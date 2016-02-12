// g++ -Wall -g -std=c++11 find-kth-largest-element.cpp && ./a.out
// Find the kth largest element in an unsorted array. Note that it is
// the kth largest element in the sorted order, not the kth distinct
// element.
// For example, given [3,2,1,5,6,4] and k = 2, return 5.
// Note: You may assume k is always valid, 1 ≤ k ≤ array's length.

// attempting solution 3:

#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>

void printArray(
	std::vector<int>::const_iterator start,
	std::vector<int>::const_iterator end)
{
	while (start != end) {
		std::cout << *start << " ";
		start++;
	}
	std::cout << std::endl;
}

void printArray(const std::vector<int>& array)
{
	printArray(array.begin(), array.end());
}

void partialSort(
	std::vector<int>::iterator start,
	std::vector<int>::iterator end)
{
	std::sort(start, end);
	printArray(start, end);
}

// Retuns Kth largest element from the array otherwise returns -1.
std::vector<int>::const_iterator findKthLargestIndex(
	std::vector<int>& array, unsigned K)
{
	std::vector<int>::const_iterator kthLargest = array.end();

	// 1. divide input array into K elements
	// and for each subarray do partial sort
	for (auto i = 0u; i < array.size(); i += K) {
		auto start = array.begin() + i;
		auto end = start + K;

		if ((i + K) >= array.size()) {
			end = array.end();
		}
		partialSort(start, end);
	}
	printArray(array);

	// 2. at this point we have K subarrays partial sorted and
	// first element of each subarray is largest; move each of
	// this element into first subarray
	for (auto i = K-2; i >= 0; i--) {
		std::swap(array[i], array[i+K]);
	}
	printArray(array);

	// 3. at this point we have all largest elements in the first
	// subarray; we sort them again and return the last element in
	// this sorted subarray as our answer

	return kthLargest;
}

int main()
{
	std::vector<int> array = {10, 2, 10,
				  30, 22, 10,
				  12, 10, -2};

	unsigned K = 4;	// Kth largest

	assert(K <= array.size());

	std::cout << "input: ";
	printArray(array);
	std::cout << "find " << K << " largest \n";

	auto kthLargest = findKthLargestIndex(array, K);
	if (kthLargest == array.end()) {
		std::cout << "\nnothing found\n";
	} else {
		std::cout << "\nfound " << *kthLargest;
	}
}
