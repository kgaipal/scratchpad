#include "rbt.h"
#include <assert.h>

RBT::RBT()
{
}

RBT::~RBT()
{
}

void RBT::insert(int value)
{
	if (!m_root.get()){
		m_root.reset(new Node(value));
		return;
	}

	// insert to left or right subtree
	Node* node = m_root.get();
	while(1) {
		if (value <= node->data) {
			if (node->left != 0) {
				node = node->left;
			} else {
				// insert here
				node->left = new Node(value);
				break;
			}
		} else {
			if (node->right != 0) {
				node = node->right;
			} else {
				// insert here
				node->right = new Node(value);
				break;
			}
		}
	}
}

void RBT::insert(const std::vector<int>& values)
{
	for (auto i = values.begin(); i != values.end();
	     i++) {
		insert(*i);
	}
}

Node* find_largest_item(Node* root)
{
	if (root == 0) {
		return 0;
	}

	Node *node = root;
	while (node->right != 0) {
		node = root->right;
	}
	return node;
}

void update_parent(Node* parent, Node* subtree, bool node_was_left_child)
{
	if (parent == 0) {
		return;
	}

	if (node_was_left_child) {
		parent->left = subtree;
	} else {
		parent->right = subtree; 
	}
}

bool RBT::remove(int value)
{
	Node *node = m_root.get();
	Node *parent = 0;

	while (node != 0) {
		if (value == node->data) {
			// found!
			// check for the children and then remove decisively
			// 4 cases below

			// 1. leaf
			if (node->left == 0 && node->right == 0) {
				update_parent(parent, 0/*leaf*/, parent->left == node);
			} 

			// 2. only left subtree exists
			else if (node->left != 0 && node->right == 0) {
				update_parent(parent, node->left, parent->left == node);
			}

			// 3. only right subtree exists
			else if (node->left == 0 && node->right != 0) {
				update_parent(parent, node->right, parent->left == node);
			}

			// 4. both left and right subtree exists
			else if (node->left != 0 && node->right != 0) {

				// find the largest child node in left subtree which has no right child
				if (Node* replacementNode = find_largest_item(node->left)) {
					update_parent(parent, replacementNode, parent->left == node);
				}
			}
			else {
				assert(true);
			}

			delete node;
			return true;
		}

		parent = node;
		if (value < node->data) {
			node = node->left;
		} else {
			node = node->right;
		}
	}

	return false;
}

bool RBT::find(int value)
{
	Node *node = m_root.get();

	while (node != 0) {
		if (value == node->data) {
			return true;
		}

		if (value < node->data) {
			node = node->left;

		} else {
			node = node->right;
		}
	}

	return false;
}

void RBT::printByLevel()
{
	std::cout << "\n[IN]";
	printInOrder(m_root.get());
	std::cout << "\n[POST]";
	printPostOrder(m_root.get());
	std::cout << "\n[PRE]";
	printPreOrder(m_root.get());

	std::cout << "\n";
}

void RBT::printInOrder(Node* node)
{
	if (node == 0) {
		return;
	}

	if (node->left != 0) {
		printInOrder(node->left);
	}

	std::cout << *node;

	if (node->right != 0) {
		printInOrder(node->right);
	}
}

void RBT::printPostOrder(Node* node)
{
	if (node == 0) {
		return;
	}

	if (node->left != 0) {
		printPostOrder(node->left);
	}

	if (node->right != 0) {
		printPostOrder(node->right);
	}

	std::cout << *node;
}

void RBT::printPreOrder(Node* node)
{
	if (node == 0) {
		return;
	}

	std::cout << *node;

	if (node->left != 0) {
		printPreOrder(node->left);
	}

	if (node->right != 0) {
		printPreOrder(node->right);
	}
}
