#ifndef _FASTDEQUE_H_
#define _FASTDEQUE_H_

#include <unordered_map>

template<typename Key, typename Object>
class FastDeque
{
private:
	class Node;
public:

	// biderectional iterator like functionality
	class Iterator
	{
	public:
		Iterator();
		Iterator& operator-- (int);
		Iterator& operator++ (int);
		Object& operator* ();

	private:
		friend class FastDeque;
		Iterator(Node* cur);

		friend bool operator != (const Iterator& lhs, const Iterator& rhs) {
			return lhs.m_current != rhs.m_current;
		}

		friend bool operator == (const Iterator& lhs, const Iterator& rhs) {
			return lhs.m_current == rhs.m_current;
		}

		Node* m_current;
	};

public:
	FastDeque();
	~FastDeque();

	Iterator begin();
	Iterator end();

	Iterator find(Key key);

	unsigned size();

	void push_back(Key key, const Object& item);
	Object pop_front();

private:
	// indexed item
	class Node
	{
	public:
		Key key;
		Object value;

		Node* next;
		Node* prev;
	};

	std::unordered_map<Key, Node> m_indexedNodes;

	Node* m_front;
	Node* m_back;
};

#include "FastDeque-inline.h"
 
#endif	// _FASTDEQUE_H_
