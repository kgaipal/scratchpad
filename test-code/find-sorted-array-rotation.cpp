#include <assert.h>
#include <iostream>
#include <sstream>
#include <vector>

const std::vector<int> rotateArray(const std::vector<int>& array, int pivot)
{
	std::vector<int> rotated(array.size());

	// for every index i in array a, a[i] is moved to a[[(i+pivot)%N]
	// where 0 <= pivot < len(array)
	const int N = array.size();
	for (int i = 0; i < N; i++) {
		const int k = (i+pivot) % N;

		rotated[k] = array[i];
	}

	return rotated;
}

int findSortedArrayRotation(const std::vector<int>& rotatedArray)
{
	if (rotatedArray.size() == 0) {
		return -1;
	}

	if (rotatedArray.size() == 1) {
		return 0;
	}

	for (int i = 1; i < rotatedArray.size(); i++) {
		if (rotatedArray[i-1] > rotatedArray[i]) {
			return i;
		}
	}

	return 0;
}

const std::string strArray(const std::vector<int>& array)
{
	std::stringstream ss;
	ss << "[";
	for (auto i : array) {
		ss << i << ",";
	}
	ss << "]";
	return ss.str();
}

int main()
{
	std::vector<int> array{1,2,3,4,5,6,7};
	std::cout << strArray(array);

	int pivot = -1;
	do {
		std::cout << "\nenter pivot [0-" << array.size()-1 << "]:";
		std::cin >> pivot;

	} while (! (0 <= pivot && pivot < array.size()) );

	const auto& rotatedArray = rotateArray(array, pivot);
	std::cout << "rotated: " << strArray(rotatedArray);

	const auto rotatedAt = findSortedArrayRotation(rotatedArray);
	assert(pivot == rotatedAt);

	std::cout << std::endl;

	return 0;
}
