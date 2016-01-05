/**
7.  Given a char pointer to large buffer of memory, write your own
version of my_malloc and my_free without using any system calls.  Make
it as robust as possible.  How would you minimize memory fragmentation?

 */

// This class is actual implementor of free()/malloc() so we cant use any of those
// functions neithg new/delete in this class.

class SlabAllocator
{
public:
	SlabAllocator(void *heap, unsigned int heapSize);

	void* malloc(unsigned int requestSize);
	void free(void* mem);

private:
	struct SlabRow;
	struct SlabHeader;
	struct SlabItem;

	SlabRow* mRoot;		// starting point to search slab linked list
	void* const mHeap;	// memory block give to us
	unsigned int mHeapSize;
	void* mUnmappedHeap;	// before this all is divided into slabs and metadata

	// Convenient numbers for pointer calculation.
	static const unsigned int slabSize;
	static const unsigned int slabDataSize;	// must be a multiple of 2^
	static const unsigned int slabRowAndSlabSize;
	static const unsigned int maxItemSizeSupported; // must be a multiple of 2^

	// Creates a new slab which will hold items of given 'itemSize'.
	SlabHeader* createSlab(unsigned int itemSize);

	// Creates a new slab row and the first slab header which will hold items of given
	// 'itemsSize'.
	SlabRow* createSlabRow(unsigned int itemsize);

	// Returns the new allocated item. It searches every header contained by the given
	// 'slr' and allocates an item from it. It fails only when there is no more memory
	// to allocate a new slab (which the new item will be allocated from). If none of
	// the existing slabs can satisfy the request, a new slab is allocated and item is
	// alloted from it.
	SlabItem* allocateItemFromSlab(SlabRow* slr);
};

unsigned int SlabAllocator::slabDataSize = 1024; // 1 KB
unsigned int SlabAllocator::slabSize = sizeof(SlabHeader) + slabDataSize;
unsigned int SlabAllocator::slabRowAndSlabSize = sizeof(SlabRow) + slabSize;
unsigned int SlabAllocator::maxItemSizeSupported = slabDataSize; // bigger require special treatment

struct SlabAllocator::SlabRow
{
	unsigned int itemSize;
	SlabHeader* firstSlab;

	SlabRow* next;

	unsigned int pad;	// padding header to 2^x bytes
};

struct SlabAllocator::SlabHeader
{
	unsigned int itemsRemaining;
	SlabItem* nextFreeItem;
	SlabHeader* next;	// next slab of same type

	unsigned int pad;	// padding header to 2^x bytes
};

struct SlabAllocator::SlabItem
{
	SlabItem* next;
};

SlabAllocator::SlabAllocator(void *heap, unsigned int mHeapSize)
	: mHeap(heap)
	, mHeapSize(mHeapSize)
	, mRoot(nullptr)
{
	if (heap == nullptr) {
		throw std::runtime_error("init failed: memory block is NULL");
	}
}

SlabHeader* SlabAllocator::createSlab(unsigned int itemSize)
{
	if ((mUnmappedHeap + SlabAllocator::slabSize) > (mHeap + mHeapSize)) {
		return nullptr;
	}

	// create slab and header inside it
	SlabHeader* sh = mUnmappedHeap;
	mUnMappedHeap += slabSize;
	sh->itemsRemaining = SlabAllocator::slabDataSize / itemSize;
	sh->nextFreeItem = sh + sizeof(SlabHeader);
	sh->next = nullptr;

	// create items inside this slab
	int i = sh->itemsRemaining - 1;
	SlabItem* si = sh->nextFreeItem;
	while (i > 0) {
		si->next = si + itemSize; // for larger itemSize, interleaved items
		si = si->next;
		i--;
	}

	si->next = nullptr;	// last item

	return sh;
}

SlabRow* SlabAllocator::createSlabRow(unsigned int itemsize)
{
	if ((mUnmappedHeap + SlabAllocator::slabRowAndSlabSize) > (mHeap + mHeapSize)) {
		return nullptr;
	}

	SlabRow* slr = mUnmappedHeap;
	mUnmappedHeap += sizeof(SlabRow);
	slr->itemSize = itemSize;
	slr->firstSlab = createSlab(itemSize);
	slr->next = nullptr;

	return slr;
}

SlabItem* SlabAllocator::allocateItemFromSlab(SlabRow* slr)
{
	if (slr == nullptr) {
		return nullptr;
	}

	SlabItem* item = nullptr;
	SlabHeader* sh = slr->firstSlab; // first slab guaranteed pre-allocated

	// search all headers until you can satisfy the request
	SlabHeader* shPrev = sh;
	sh = sh->next;

	while (sh != nullptr) {
		if (sh->itemsRemaining > 0) {
			break;
		}
		shPrev = sh;
		sh = sh->next;
	}

	if (sh == nullptr) {
		sh = shPrev->next = createSlab(itemSize);
	}

	// if request still fails, we return nullptr
	if (sh != nullptr) {
		item = sh->nextFreeItem;
		sh->nextFreeItem = sh->nextFreeItem->next;
		--(sh->itemsRemaining);
	}

	return item;
}

void* SlabAllocator::malloc(unsigned int requestSize)
{
	SlabRow* slr = nullptr;

	// calculate item size to allocate for this request;
	// itemSize will come out as multiple of 2 so that we
	// can find right slab_row based on this computation
	unsigned int itemSize = 1;
	for (int i = 0; itemSize < requestSize; i++) {
		itemSize <<= i;
		if (itemSize > slabDataSize) {
			break;	// process this as special block
		}
	}

	// iterate on the slab headers linked list to find the right spot

	// TODO: process as special block
	if (itemSize > maxItemSizeSupported) {
		throw std::runtime_error("special block not yet supported");
	}

	// find the correct slab header for this item
	// otherwise create a new slab header
	SlabRow* slr = mRoot;
	SlabRow* slrPrev = (slr == nullptr? nullptr : slr->next);
	while (slr != nullptr) {
		if (slr->itemSize == itemSize) {
			break;
		}
		slrPrev = slr;
		slr = slr->next;
	}

	// create a new slab row for this item on demand
	if (slr == nullptr) {
		slr = createSlabRow(itemSize);

		if (slrPrev == nullptr) {
			mRoot = slr; // this was first ever request
		} else {
			slrPrev->next = slr;
		}
	}

	// return the allocated item from this slab, it can be nullptr if no more memory
	return (void*)(allocateRequestFromSlab(slr, itemSize));
}

void SlabAllocator::free(void* mem)
{
	// dont know about this range
	if (mem < mHeap || mUnmappedHeap <= mem) {
		return;
	}

	SlabItem* newItem = (SlabItem*)mem;

	// first find the slab row
	SlabRow* slr = mRoot;
	SlabRow* slrPrev = nullptr;
	while (slr != nullptr) {

		// each new slab row was allocated with increasing distance from its older
		// sibling; find closest slab row this address may belong to
		// (slab_row_address < newItem)
		if (slrPrev < newItem && newItem < slr) {
			break;	// found
		}
		slrPrev = slr;
		slr = slr->next;
	}

	// this must be most recent (farthest from mRoot) slab row allocated
	if (slr == nullptr) {
		slr = slrPrev;
	}

	// second find the slab header for this row
	SlabHeader* sh = slr->firstSlab;
	while (sh != nullptr) {

		// address within slab block?
		if (sh < newItem && newItem < (sh + SlabAllocator::slabSize)) {
			break;	// found
		}
		sh = sh->next;
	}

	if (sh == nullptr) {
		return;		// most unlikely but still ...
	}

	// join this in the items list, insert in the front
	SlabItem* p = sh->nextFreeItem;
	sh->nextFreeItem = newItem;
	newItem->next = p;

	++(sh->itemsRemaining);
}

int main()
{
	char heap[4096];	// 4KB
	SlabAllocator s(heap);

	char* p1 = (char*)s.malloc(3);	// 3 bytes
	s.free(p1);

	char* p2 = (char*)s.malloc(8); // 8 bytes
	s.free(p2);

	char* p3 = (char*)s.malloc(1024); // 1Kbytes
	s.free(p3);

	return 0;
}
