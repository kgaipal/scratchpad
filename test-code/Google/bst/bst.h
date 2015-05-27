// Binary Search Tree implementation
// also includes various other operations you can do on binary search tree like printing, deleting

#include <iostream>
#include <memory>
#include <vector>

#include "node.h"

class BST
{
public:
	BST();
	~BST();

	void insert(int value);
	void insert(const std::vector<int>& values);

	// first node matching with the given value
	bool remove(int value);

	// return true if any matching given value in bst
        bool find(int value);

	// print whole tree level by level
	void printByLevel();

	static void printInOrder(Node* node);
	static void printPostOrder(Node* node);
	static void printPreOrder(Node* node);

private:
	std::unique_ptr<Node> m_root;
};
