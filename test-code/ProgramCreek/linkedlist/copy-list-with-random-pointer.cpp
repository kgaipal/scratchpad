//
// http://www.programcreek.com/2012/12/leetcode-copy-list-with-random-pointer/

#include <iostream>
#include <unordered_map>
#include <vector>

struct Node {
	Node()
	    : next(nullptr)
	    , random(nullptr)
	{
	}

	Node* next;
	Node* random;
};

void printLinkedList(Node* head)
{
	Node* node = head;
	while (node != nullptr) {
		node = node->next;
	}
	std::cout << std::endl;
}

Node* clone(Node* src)
{
	Node* cloned = nullptr;

	std::unordered_map<
		Node*,		/*original*/
		Node*		/*clone*/
	> cloneMap;

	std::unordered_map<
		Node*,		   /*head*/
		std::vector<Node*> /*tails*/
	> associationMap;

	Node* p1 = src;
	Node* p2 = cloned;
	while (p1 != nullptr) {
		Node* node = new Node();

		// save clone node i.e. A -> A'
		cloneMap[p1] = node;

		if (p2) {
			p2->next = node;
		} else {
			cloned = p2 = node;
		}

		// save association too
		if (p1->random) {
			associationMap[p1->random/*head*/]
				.push_back(p1/*tail*/);
		}

		p1 = p1->next;
		p2 = p2->next;
	}

	// update the random pointers for cloned list
	for (auto& it : associationMap) {
		auto head = it.first;

		// update random for each tail in cloned linked list
		for (auto& tail : it.second) {
			cloneMap[tail]->random = head;
		}
	}

	return cloned;
}

int main()
{
	Node* src = nullptr; // ideally non-empty

	Node* dest = clone(src);

	printLinkedList(dest);
}
