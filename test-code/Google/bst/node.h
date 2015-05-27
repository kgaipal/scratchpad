#ifndef _node_h_
#define _node_h_

// represents a node for any tree
// should hold any data type
#include <iostream>

class Node
{
public:
	int data;

	Node* left;
	Node* right;

	Node(int data);

	friend std::ostream& operator<<(std::ostream& out, const Node& node)
	{
		std::cout << " " << node.data << " ";
		return out;
	}
};

#endif	// _node_h_
