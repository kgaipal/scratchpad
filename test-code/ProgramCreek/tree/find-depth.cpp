//
// http://www.programcreek.com/2013/02/leetcode-minimum-depth-of-binary-tree-java/

// traverse level by level and check if any leaf discovered
// if yes thats is the depth we were looking for

unsigned findDepth(Node* root)
{
	unsigned depth = 0;

	Queue nodesAtThisLevel;
	allNodes.enqueue(root, 0);

	while (!nodesAtThisLevel.empty()) {
		curr,level = allNodes.deque();

		if (isLeaf(curr)) {
			return level;
		}

		// save its children in queue again
		if (curr->left) {
			allNodes.enqueue(curr->left,++depth);
		}

		if (curr->right) {
			allNodes.enqueue(curr->right,++depth);
		}
	}

	return depth;
}
