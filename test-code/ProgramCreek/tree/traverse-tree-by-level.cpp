//
// tau's MS interview

// traverse tree level by level
// better suggestion by tau: use two stacks, one for all current level of nodes you are working on and other for pushing next level children

struct Node {

	Node(int d)
		: data(d)
		, left(nullptr)
		, right(nullptr)
	{ }

	Node* left;
	Node* right;
	int data;

	void print() {
		std::cout << data << std::endl;
	}
};

void traverse_bfs(Node* root)
{
	Queue myq;

	if (root == nullptr) {
		return;
	}

	myq.enqueue(root);

	while (!myq.empty()) {
		unsigned itemsAtThisLevel = myq.size();

		while ((itemsAtThisLevel--) > 0) {
			Node* m_last = deque();
			m_last->print();

			// next level items
			if (m_last->left)
				myq.enqueue(m_last->left);

			if (m_last->right)
				myq.enqueue(m_last->right);

		} // go to next sibling at the same level
	}
}

Node* createTree(std::const_forward_iterator begin, std::const_forward_iterator end)
{
	Node* root = nullptr;
	while (begin != end) {

	}
}

int main ()
{
	Node* root = createTree(std::vector<int>({12, 23, 56, 90}));

	traverse_bfs(root);

	return 0;
}
