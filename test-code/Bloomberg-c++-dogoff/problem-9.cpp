/**
9.  Given the function: "bool numExists( int array[], int array_len,
int num )" where "array" is a sorted array of integers.  Determine if
"num" exists in the array.  This is basically a binary search question.
Do a recursive version and an iterative version.  Writing binary search
is easy but getting it the most efficient is hard.  Can you do it with
the minimum number of operations possible?

sol:

This is similar to binary search. We can visualize this as the middle item of the given
array as root of the BST and keep jumping the left subtree and subtree finding their root
until item is found or not found. The optimizing is that we check the item in the range of
each such subtree we are working on. This saves us from getting down log n depth to decide
if item is not found if its larger than the largest in the subtree we are working. This
will always hold true because this array and subsequently each subarray/subtree is sorted.

So at max O(log n) steps to decide if item is in the array (iff its in the range of
subarray wee are working).

Both versions have "optimizing statements" marked which will make sure we dont search item
beyond first and last item in the given array.

*/

// recursive
bool numExist(int array[], int len, int num)
{
	if (len < 1) {
		return false;
	}

	// base case
	if (len == 1) {
		return (array[0] == num);
	}

	// optimization statement
	if (num < array[0]) {
		return false;
	}

	// optimization statement
	if (array[len-1] < num) {
		return false;
	}

	// get middle (root) of this array
	const int root = ((len%2) == 0? len/2: (len+1)/2);

	// check if the num is right at root?
	if (num == array[root]) {
		return true;
	}

	// may be in left subtree?
	if (num < array[root]) {
		return numExist(array[0], root, num);
	}

	// or in right subtree?
	return numExist(array[root+1], (len-(root+1)), num);
}


// iterative
bool numExist(int array[], int len, int num)
{
	int start = 0;
	int end = len-1;

	bool found = false;

	auto rootIndex = [] (int start, int end) {
		const int n = end-start+1;

		if (n%2 == 0) {
			return start + n/2; // even
		}
		return start + (n-1)/2;	// odd
	};

	while (!found) {
		const int items = end-start+1;

		if (items < 1) {
			break;	// empty array
		}

		const int root = rootIndex(start, end);

		if (items == 1) {
			found = (array[root] == num);
			break;	// single item array
		}

		// optimizing statement
		if (num < array[start]) {
			break;
		}

		// optimizing statement
		if (array[end] < num) {
			break;
		}

		if (num == array[root]) {
			found = true;
			break;	// found at root
		}

		if (num < array[root]) {
			end   = root - 1; // left subtree
		} else {
			start = root + 1; // right subtree
		}
	}

	return found;
}
