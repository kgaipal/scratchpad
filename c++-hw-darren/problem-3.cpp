/**
3.  Given the root node to a singly linked list, write an algorithm to
see if it loops back on itself somewhere in the middle.

Sol:
Start two pointers, a faster pointer which will jump 2 nodes at a time and a regular
one which will jump one node at a time. The faster node will enter the cycle earlier and
keep visiting every node in cycle and will be equal to regular pointer only somwhere in
the cycle, that is the cycle detection.

For a flat linked list they will never meet and nullptr check for faster pointer will
break out of the loop first.

 */

bool isCyclic(Node* head)
{
	if (head == nullptr) {
		return false;
	}

	Node* n = head;
	Node* fast = head;

	do {
		n = n->next;
		if (n == nullptr) {
			break
		}

		fast = fast->next;
		if (fast == nullptr) {
			break
		}

		fast = fast->next;
		if (fast == nullptr) {
			break
		}

	} while (fast != n);

	return (fast == n);
}
