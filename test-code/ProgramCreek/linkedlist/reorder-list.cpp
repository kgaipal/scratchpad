//
// http://www.programcreek.com/2013/12/in-place-reorder-a-singly-linked-list-in-java/


#include <iostream>
#include <vector>

struct Node {
	Node(int item)
	    : next(nullptr)
	    , data(item) {
	}

	Node* next;
	int data;
};

namespace NodeHelper
{

void printLinkedList(Node* const head)
{
	Node* n = head;
	unsigned i = 0;
	while (n != nullptr) {
		std::cout << " " << n->data;
		n = n->next;
		i++;
	}

	std::cout << (i%2==0?" even":" odd") << std::endl;
}

Node* append(Node* const head, int item)
{
	if (head == nullptr) {
		return new Node(item);
	}

	// travel till end and append item
	Node* n = head;
	while (n->next != nullptr) {
		n = n->next;
	}

	n->next = new Node(item);
	return head;
}

Node* createLinkedList(const std::vector<int>& src)
{
	Node* head = nullptr;
	for (auto& item : src) {
		head = append(head, item);
	}

	return head;
}

} // namespace NodeHelper

void reorder(Node* head)
{
	if (head == nullptr) {
		return;		// nothing to work upon
	}

	// 1. find the length of the list

	// 2. walk down till middle of the list

	// 3. from pivot of list [repeat till remaining nodes are processed]:
	//   3.1 hold onto middle of list, and
	//   3.2 advance two probe pointers to eol and eol-1, and
	//   3.3 hold on the head of list and move eol-1 to head+1
	//   3.4 move head+1 to head+1->next->next


	Node* begin = head;
	Node* pivot = nullptr;
	unsigned len = 1;

	// find pivot and length of the linked list
	{
		// length
		Node* curr = head;
		while (curr->next != nullptr) {
			curr = curr->next;
			len++;
		}

		len++;

		curr = head;
		auto pivotPoint = [&] () {
			if (len % 2) {
				return (len-1)/2; // odd: middle
			}

			return (len/2)-1; // even: closer to end
		};

		const unsigned p = pivotPoint();
		for (unsigned i = 0; i < p; i++) {
			curr = curr->next;
		}
		pivot = curr;
	}

	// send probes from pivot towards end and re-rorder from that point
	while (pivot->next != nullptr) {
		// send two probes from pivot (curr1 leads curr2)
		Node* curr1 = pivot->next;
		Node* curr2 = pivot;

		unsigned i = 0;
		// reach till end
		while (curr1->next != nullptr) {
			i++;
			curr2 = curr1;
			curr1 = curr1->next;
		}

		// insert curr1 after begin and update list next ptrs
		Node* tmp = begin->next;
		curr1->next = tmp;
		begin->next = curr1;

		curr2->next = nullptr;

		// advance begin
		begin = begin->next->next;
	} // while
}

int main()
{
	unsigned items = 6;
	std::vector<int> data;
	{
		for (unsigned  i = 0; i < items; i++) {
			data.push_back(i);
		}
	}

	Node* head = NodeHelper::createLinkedList(data);
	NodeHelper::printLinkedList(head);

	std::cout << "after reordering\n";
	reorder(head);
	NodeHelper::printLinkedList(head);
}
