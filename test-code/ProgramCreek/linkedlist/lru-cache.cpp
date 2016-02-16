//
// a LRU Cache
// http://www.programcreek.com/2013/03/leetcode-lru-cache-java/

#include <unordered_map>

struct Node {
	Node(int d)
		: data(d)
		, next(nullptr)
		, prev(nullptr) {
	}

	int data;
	Node* next;
	Node* prev;
};

class OrderedItems
{
public:
	OrderedItems();
	~OrderedItems();

	unsigned count() const { return m_itemsCount; }

	void addToFront(Node* node);
	void removeFromEnd();
	void moveFront(Node* node);

private:
	Node* m_head;
	Node* m_tail;
	unsigned m_itemsCount;
};

class LRUCache
{
public:
	void set(int key, int value);
	int get(int key);

private:
	const unsigned kMaxCacheSize;

	std::unordered_map<int, Node*> m_keyMap;

	// doubly linked list to store items in order
	OrderedItems m_orderedItems;

	void markRecentlyUsed(Node* node);
	void addNew(Node* node);
};

void OrderedItems::addToFront(Node* node)
{
	if (m_head == nullptr) {
		// first element
		m_head= m_tail = node;
	} else {
		Node* tmp = m_head;
		m_head = node;
		tmp->prev = m_head;
		m_head->prev = nullptr;
		m_head->next = tmp;
	}

	++m_itemsCount;
}

void OrderedItems::removeFromEnd()
{
	if (m_head == nullptr) {
		return;
	}

	if (m_head == m_tail) {
		// only one element
		delete m_head;

		m_head = m_tail = nullptr;
	} else {
		// more than one element, drop last
		Node* tmp = m_tail->prev;
		m_tail = m_tail->prev;
		m_tail->next = nullptr;

		delete tmp;
	}

	--m_itemsCount;
}

void OrderedItems::moveToFront(Node* node)
{
	// change the order of the given node; bring to front

	// only one node; nothing to do
	if (m_head == m_tail) {
		return;
	}

	// already at correct place; nothing to do
	if (node == m_head) {
		return;
	}

	// node is either last or somewhere in middle
	Node* tmp = node->prev;
	tmp->next = node->next;

	m_head->prev = tmp;
	m_head = m_head->prev;
}

void LRUCache::addNew(Node* node)
{
	// drop last element and add new to front
	if (m_orderedItems.count() > kMaxCacheSize) {
		m_orderedItems.removeFromEnd();
	}
	m_orderedItems.addToFront(node);
}

void LRUCache::markRecentlyUsed(Node* node)
{
	m_orderedItems.moveToFront(node);
}

void LRUCache::set(int key, int value)
{
	// find, if exists, replace
	auto it = m_keyMap.find(key);
	if (it == m_keyMap.end()) {

		// add to front of linked list
		Node* node = new Node(value);
		addNew(node);

		m_keyMap[key] = node;
	} else {
		// replace existing and move to front
		(*it)->data = value;
		markRecentlyUsed(*it);
	}
}

int LRUCache::get(int key)
{
	auto it = m_keyMap.find(key);
	if (it == m_keyMap.end()) {
		return -1;
	}

	int value = it->data;

	// move to front of the cache
	markRecentlyUsed(*it);

	return value;
}
