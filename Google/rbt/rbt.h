// Red Black Tree implementation
// also includes various other operations you can do on binary search tree like printing, deleting

#include <iostream>
#include <memory>
#include <vector>

#include "node.h"

class RBT
{
public:
	RBT();
	~RBT();

	void insert(int value);

	// first node matching with the given value
	bool remove(int value);

	// return true if any matching given value in rbt
        bool find(int value);

	// print whole tree level by level
	void printByLevel();

	static void printInOrder(Node* root);
	static void printPostOrder(Node* root);
	static void printPreOrder(Node* root);

private:
	std::unique_ptr<Node> m_root;

	void rotate_left();
	void rotate_right();
	void colorize();

};
