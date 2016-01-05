/**
1.  You have a ladder n-steps in height.  You can either take one step
or two steps up the ladder at a time.  How can you find out all the
different combinations up the ladder?  Then figure out an algorithm that
will actually print out all the different ways up the ladder.  ie:
1,1,2,1,2,2... etc...

Sol: BST

We can visualize this as a binary decision making tree. We start with a root node where we
have still N steps to climb. If we take one step (left subtree) on the ladder we have N-1
steps left to take, if we take 2 steps (right subtree) on the ladder we have N-2 steps
left to take. So each node in this BST represents a ladder step with root node as
exception representing no step on the ladder.

While making this tree path we have to remember the path we have come from so we have a
data member 'pathTraveled' wihth 1 or 2 appended before waling down that path. We print
this string path when we reach the top ('stepsLeft' == 0). Thus, this forms our base case.
We take two steps only when possible.

Time complexity for this will be bounded by O(log N). The tree size keeps decreasing as
there are fewer steps left to take on way up to the ladder top. So we can visaualize this
tree as a lot of nodes with 1s or 2s on the left.

*/

#include <iostream>

class Node
{
public:
	Node(unsigned int stepsLeft, const char* _pathTraveled, char newStep)
		: stepsLeft(stepsLeft)
		, oneStep(nullptr)
		, twoStep(nullptr)
	{
		// append the newStep to the given path
		pathLength = strlen(strlen(_pathTraveled) + 1 /* + newStep*/);
		pathTraveled = malloc(sizeof(char) * pathLength);

		strpcy(pathTraveled, _pathTraveled);
		pathTraveled[pathLength-2] = newStep; // append
	}

	char* pathTraveled;
	const unsigned int stepsLeft;

	Node* oneStep;
	Node* twoStep;
};

void explorePath(Node* root)
{
	if (root == nullptr) {
		return;
	}

	// have reached top of the ladder
	// print the path you came on before returning
	if (root->stepsLeft == 0) {
		std::cout << root->pathTraveled + "\n";
		return;
	}

	// not yet at the top: one step always possible
	root->oneStep = new Node(root->stepsLeft-1, root->pathTraveled, '1');
	explorePath(root->oneStep);

	// not yet at the top: two steps possible?
	if (root->stepsLeft-2 >= 0) {
		root->twoStep = new Node(root->stepsLeft-2, root->pathTraveled, '2');
		explorePath(root->twoStep);
	}
}

void printSteps(unsigned int stepsInLadder)
{
	Node* root = new Node(stepsInLadder, ""/*nothing traveled so far*/);
	explorePath(root);

	// when program dies all will be reclaimed, no memory leaks
}

int main()
{
	printSteps(10);		// say 10 steps in ladder
	return 0;
}
