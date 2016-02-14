//
// http://www.programcreek.com/2014/03/leetcode-symmetric-tree-java/


void flattenTree(Node* root, Queue& allNodes, bool leftFirst)
{
	Queue allNodesAtLevel;
	allNodesAtLevel.enqueue(root);

	// traverse it level by level, insert left most first in the
	// order if requested as such
	do {
		curr = allNodesAtLevel.deque(); // current work set

		allNodes.enqueue(curr);	// final flattened list so far

		if (!curr) {
			break;
		}
		if (leftFirst) {
			allNodesAtLevel.enqueue(curr->left);
			allNodesAtLevel.enqueue(curr->right);
		} else {
			allNodesAtLevel.enqueue(curr->right);
			allNodesAtLevel.enqueue(curr->left);
		}
	} while (true);
}

bool isSymmetric(Node* root)
{
	if (root == nullptr) {
		return true;
	}

	Queue leftSubtree;
	Queue rightSubtree;

	leftSubtree.push(root->left);
	rightSubtree.push(root->right);

	flattenTree(root->left, leftSubtree, true);
	flattenTree(root->right, rightSubtree, false);

	// compare leftSubtree and rightSubtree contents
	while (!leftSubtree.empty() && !rightSubtree.empty()) {
		if (leftSubtree.pop() == rightSubtree.pop()) {
			;; /// keep going
		}
	}

	return (leftSubtree.empty() && rightSubtree.empty());
}

int main()
{
	return 0;
}
