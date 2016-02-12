//
// http://www.programcreek.com/2012/12/add-two-numbers/

#include <iostream>

struct Node {
	Node(unsigned item)
	    : data(item)
	    , next(nullptr)
	{
	}

	unsigned data;
	Node* next;
};

namespace Helper {

Node* createLinkedList(unsigned number)
{
	std::cout << "Creating list from:" << number << std::endl;

	// parse the digits and create a linked list with least
	// significant digit as HEAD
	Node* head = nullptr;
	Node* curr = head;

	if (number == 0) {
		return new Node(0);
	}

	while (number) {
		Node* node = new Node(number%10);
		if (head == nullptr) {
			head = curr = node;
		} else {
			curr->next = node;
			curr = curr->next;
		}
		number = number/10;
	}

	return head;
}

void printLinkedList(Node* head)
{
	Node* node = head;
	while (node != nullptr) {
		std::cout << node->data << " ";
		node = node->next;
	}
	std::cout << std::endl;
}

};

Node* copy(Node* src)
{
	Node* head = nullptr;
	Node* curr = head;

	while (src != nullptr) {
		Node* node = new Node(src->data);

		if (head == nullptr) {
			head = curr = node;
		} else {
			curr->next = node;
			curr = curr->next;
		}
		src = src->next;
	}

	return head;
}

Node* add(Node* op1, Node* op2)
{
	Node* head = nullptr;
	Node* curr = head;

	// -- addition logic here --
	bool carry = false;
	while (op1 != nullptr && op2 != nullptr) {

		// keep adding each digit and also carry
		Node* node = new Node(carry?1:0);

		node->data += (op1->data + op2->data);
		carry = (node->data > 9);
		if (carry) {
			node->data = node->data%10;
		}

		// advance
		if (head == nullptr) {
			head = curr = node;
		} else {
			curr->next = node;
			curr = curr->next;
		}
		op1 = op1->next;
		op2 = op2->next;
	}

	if (op1 == nullptr && op2 == nullptr) {
		// both empty list nothing to add

	} else if (op1 == nullptr || op2 == nullptr) {

		Node* node = nullptr;

		// copy remaining digits to result
		if (op1 == nullptr) {
			node = copy(op2);
		} else {
			node = copy(op1);
		}

		if (head == nullptr) {
			head = curr = node;
		} else {
			curr->next = copy(op2);
			curr = curr->next;
		}
	}

	return head;
}

int main()
{
	Node* op1 = Helper::createLinkedList(0);
	// Node* op1 = Helper::createLinkedList(342);
	Helper::printLinkedList(op1);

	Node* op2 = Helper::createLinkedList(100);
	// Node* op2 = Helper::createLinkedList(465);
	Helper::printLinkedList(op2);

	Node* result = add(op1, op2);
	std::cout << "result:";
	Helper::printLinkedList(result);
}
