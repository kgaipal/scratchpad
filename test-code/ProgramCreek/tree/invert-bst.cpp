//
// invert a binary tree
// http://www.programcreek.com/2014/06/leetcode-invert-binary-tree-java/

struct Node {
	Node(int d)
		: data(d), left(nullptr), right(nullptr) {
	}

	int data;
	Node* left;
	Node* right;
};

void addNode(Node* root, Node* node)
{
	if (node->data <= root->data) {
		// smaller is right child (reverse order)
		if (root->right == nullptr) {
			root->right = node;
		} else {
			addNode(root->right, node);
		}
	} else {
		// larger is left child
		if (root->left == nullptr) {
			root->left= node;
		} else {
			addNode(root->left, node);
		}
	}
}

void invertBST(Node* root)
{
	// scan level-by-level tree under root and store in queue for
	// each level, move the nodes into a new BST with reverse order

	Queue nodesAtThisLevel;
	nodesAtThisLevel.enqueue(root);
	nodesAtThisLevel.enqueue(nullptr);

	while (!nodesAtThisLevel.empty()) {
		Node* curr = nodesAtThisLevel.deque();

		// stash into another queue for reconstructing
		allNodes.enqueue(curr);

		//add children to current queue
		if (curr->left) nodesAtThisLevel.enqueue(curr->left);
		if (curr->right) nodesAtThisLevel.enqueue(curr->right);
	}

	// now we have all the nodes available in ‘allNodes’ which
	// will be used to reconstruct new BST
	Node* newBSTRoot = allNodes.dequeue();
	while (!allNodes.empty()) {
		Node* curr = allNodes.dequeue();
		addNode(newBSTRoot, curr);
	}
}
