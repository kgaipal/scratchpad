#include <iostream>

void build_heap(int array[], unsigned int size);
void max_heapify(int array[], unsigned int start, unsigned int size);
void heapsort(int array[], unsigned int size);

void print_array(int array[], unsigned int size)
{
	std::cout << "\t";
	for (unsigned int i = 0; i < size; i++) {
		std::cout << array[i];
		if (i != size-1) std::cout << ", ";
	}
	std::cout << "\n";
}

void swap(int* val1, int* val2)
{
	int temp = *val1;
	*val1 = *val2;
	*val2 = temp;
}

void build_heap(int array[], unsigned int size)
{
	for (int i = size/2; i >= 0; i--) {
		max_heapify(array, i, size);
	}
}

void max_heapify(int array[], unsigned int start, unsigned int size)
{
	if (array == nullptr) {
		return;
	}

	// const unsigned int size = sizeof(array)/sizeof(array[0]);
	const unsigned int parent = start;
	const unsigned int left_child = 2*parent + 1;
	const unsigned int right_child = 2*parent + 2;
	
	unsigned int largest = parent;

	if (left_child < size && array[left_child] > array[largest]) {
		largest = left_child;
	}

	if (right_child < size && array[largest] < array[right_child]) {
		largest = right_child;
	}

	// parent was not the largest of three
	if (parent != largest) {
		swap(&array[largest], &array[parent]);
		max_heapify(array, largest, size);
	}
}

void heapsort(int array[], unsigned int size)
{
	if (array == nullptr) {
		return;
	}

	// build the heap for first time; O(n) complexity
	build_heap(array, size);

	std::cout << "bh: ";
	print_array(array, size);

	swap(&array[0], &array[size-1]);
	// top element is max, shrink the array size and work on the remaining
	for (int i = size-1 ; i > 0; i--) {
		std::cout << i << "|";
		print_array(array, size);
		swap(&array[0], &array[i]);
		max_heapify(array, 0, i-1);
	}
}

int main()
{
	int array[] = {2, 1, 0, 5, 4, 10, 6};
	unsigned int size = sizeof(array)/sizeof(array[0]);

	std::cout << "before:";
	print_array(array, size);

	heapsort(array, size);

	std::cout << "final:";
	print_array(array, size);

	return 0;
}
