/**
8.  Implement quicksort().

Sol:
Implementing a recursive version of quicksort. This is template style. There are three
possible implementations of quicksort based on the pivot element to choose. If we choose
first or last element as pivot and if the list is already sorted, algorithm will always
run in O(n^2). If however, we choose middle element as pivot, even as the list is already
sorted complexity will not be O(n^2) since partitioning depth will not go more than log n.

Another possiblity is implement an iterative version of quicksort (to avoid deep
recursion). In this case space complexity will still be O(log n) but relatively less
expensive than recursive version. This can be done using a stack. I have not written there
though. I have it on paper.

*/

// This function will always take first element in the given array as pivot, it can be
// worst for an alrady sorted list O(n^2) worst case for already sorted list otherwise
// O(n log(n)) complexity.
template<typename T>
void qsort0(std::vector<T>& data, const int& start, const int& end)
{
	if (start >= end || start < 0) {
		return;
	}

	if ((end - start) < 2) {
		return;		// single element is considerd sorted
	}

	T pivot = data[start];	// always first item is our pivot
	int l = start;
	int r = end;

	while (l < r) {
		while (l < r && pivot < data[r]) {
			r--;
		}

		// if we have not exhausted all items then data[r] is smaller than pivot,
		// move data[r] to right position w.r.t to pivot
		if (l != r) {
			data[l++] = data[r];
		}

		while (l < r && data[l] <= pivot) {
			l++;
		}

		// if we have not exhausted all items then data[l] is larger than pivot,
		// move data[l] to right position w.r.t to pivot
		if (l != r) {
			data[r--] = data[l];
		}
	}

	data[l] = pivot;	// or data[r] = pivot

	// do for remaining left and right partitions
	qsort0<T>(data, start, l-1);
	qsort0<T>(data, l+1, end);
}

// This function will always take last element in the given array as pivot, it can be
// worst for an alrady sorted list O(n^2) worst case for already sorted list otherwise
// O(n log(n)) complexity.
template<typename T>
void qsortN(std::vector<T>& data, const int& start, const int& end)
{
	if (start >= end || start < 0) {
		return;
	}

	if ((end - start) < 2) {
		return;		// single element is considerd sorted
	}

	T pivot = data[end];	// always last item is our pivot
	int l = start;
	int r = end;

	while (l < r) {
		while (l < r && data[l] <= pivot) {
			l++;
		}

		// if we have not exhausted all items then data[l] is larger than pivot,
		// move data[l] to right position w.r.t to pivot
		if (l != r) {
			data[r--] = data[l];
		}

		while (l < r && pivot < data[r]) {
			r--;
		}

		// if we have not exhausted all items then data[r] is smaller than pivot,
		// move data[r] to right position w.r.t to pivot
		if (l != r) {
			data[l++] = data[r];
		}
	}

	data[l] = pivot;	// or data[r] = pivot

	// do for remaining left and right partitions
	qsort0<T>(data, start, l-1);
	qsort0<T>(data, l+1, end);
}

// This function will always take middle element in the given array as pivot, it can be
// worst for an already sorted list O(n^2) worst case for already sorted list otherwise
// O(n log(n)) complexity.
template<typename T>
void qsortMiddle(std::vector<T>& data, const int& start, const int& end)
{
	if (start >= end || start < 0) {
		return;
	}

	if ((end - start) < 2) {
		return;		// single element is considerd sorted
	}

	// if even number of items we choose
	auto findMiddle = [&] () {
		if (((end-start) % 2) == 0) {
			return ((end-start)/2) // odd items
		}

		// even items take (n/2)+1 item since we are starting from left element
		// first in the given data
		return ((end-start+1)/2;
	};

	T pivot = data[findMiddle()]; // always middle item is our pivot
	int l = start;
	int r = end;

	while (l < r) {
		while (l < r && data[l] <= pivot) {
			l++;
		}

		// if we have not exhausted all items then data[l] is larger than pivot,
		// move data[l] to right position w.r.t to pivot
		if (l != r) {
			data[r--] = data[l];
		}

		while (l < r && pivot < data[r]) {
			r--;
		}

		// if we have not exhausted all items then data[r] is smaller than pivot,
		// move data[r] to right position w.r.t to pivot
		if (l != r) {
			data[l++] = data[r];
		}
	}

	data[l] = pivot;	// or data[r] = pivot

	// do for remaining left and right partitions
	qsort0<T>(data, start, l-1);
	qsort0<T>(data, l+1, end);
}

template<typename T>
void quicksort(std::vector<T>& data)
{
	// 1. Choose first element as pivot to partition
	// qsort0<T>(data, 0, data.size()-1);

	// 2. Choose last element as pivot to partition
	// qsortN<T>(data, 0, data.size()-1);

	// 3. Choose middle element as pivot to partition
	// qsortMiddle<T>(data, 0, data.size()-1);
}
