/**
2. Given the root node to a singly linked list, reverse the last 5
nodes in the list.

Sol:
I spent little more time than expected here in updating logic for end conditions! I
designed this problem to reverse last N nodes not just 5. Start from the head in the
linked list and find the sublist to reverse. If the given linked list is larger than N
items, reverse the complete list else keep moving till the end and find a linked list
[start, end] and reverse it. A pointer to the node before 'start' is 'preStart' which is
end point where reverse list will be appended at the end. I stumbled more on finding
corner cases and lost track of time.

 */

#include <iostream>
#include <vector>

// reverses the given list
Node* reverseList(Node* head)
{
	if (head == nullptr) {
		return nullptr;
	}

	Node* reversed = head;

	// make current head the last node, new nodes will be inserted in front
	Node* n = reversed->next;
	reversed->next = nullptr;

	// invariant: 'reversed' is the head of the reversed sublist
	while (n != nullptr) {
		Node* p = n->next;
		n->next = reversed;
		reversed = n;	// update the head for the reversed list
		n = p;		// advance to next available node to reverse
	}
	return reversed;
}

// reverse last N items in the given linked list in 'head'
Node* reverseLastN(Node* head, unsigned int lastN)
{
	if (head == nullptr) {
		return nullptr;
	}

	// 1. find the sublist to reverse
	Node* preStart = head;	// at or 1 node before the sublist to reverse
	{
		Node* start = head;
		Node* end = head;

		int sublistLength = 0;

		// invariants:
		// 1. [start, end] is the sublist we want to reverse
		// 2. sublistLength <= lastN
		// 3. 'preStart' must be at or 1 node before 'start'
		// 4. there must be exactly 'sublistLength' nodes between [start, end]
		while (end->next != nullptr) {
			end = end->next;

			if (sublistLength < lastN) {
				sublistLength++;
			} else {
				// if we never hit this else case, then preStart, head,
				// start are all same i.e. whole list is to be reversed
				preStart = start;
				start = start->next;
			}
		}
	}

	// 2. reverse sublist found above
	if (preStart == head) {
		head = preStart = reverseList(preStart); // reverse whole list
	} else {
		preStart->next = reverseList(preStart->next);
	}

	return head;
}

int main(/*no args*/)
{
	std::vector<int> v{3,5,8,0,1,2,3,4,5};
	Node* head = makeList(v); // assume function exist

	head = reverseLastN(head, 5);
	print(head);		// assume function exist

	return 0;
}
