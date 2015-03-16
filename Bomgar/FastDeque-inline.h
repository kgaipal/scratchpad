#include "FastDeque.h"

template<typename Key, typename Object>
FastDeque<Key, Object>::FastDeque()
	: m_front(NULL)
	, m_back(NULL)
{
}

template<typename Key, typename Object>
FastDeque<Key, Object>::~FastDeque()
{
}

template<typename Key, typename Object>
typename FastDeque<Key, Object>::Iterator FastDeque<Key, Object>::begin()
{
	return Iterator(m_front);
}

template<typename Key, typename Object>
typename FastDeque<Key, Object>::Iterator FastDeque<Key, Object>::end()
{
	return Iterator(NULL);
}

template<typename Key, typename Object>
typename FastDeque<Key, Object>::Iterator FastDeque<Key, Object>::find(Key item)
{
	auto it = m_indexedNodes.find(item);
	if (it == m_indexedNodes.end()) {
		return end();
	}

	return Iterator(&(it->second));
}

template<typename Key, typename Object>
unsigned FastDeque<Key, Object>::size()
{
	return m_indexedNodes.size();
}

template<typename Key, typename Object>
Object FastDeque<Key, Object>::pop_front()
{
	if (m_front == NULL) {
		return Object();
	}

	// popped item
	Object item(m_front->value);

	// update pointers
	Node& n = *m_front;
	m_front = m_front->next;
	m_front->prev = NULL;

	// delete this node and its index
	m_indexedNodes.erase(n.key);

	return item;
}

template<typename Key, typename Object>
void FastDeque<Key, Object>::push_back(Key key, const Object& item)
{
	// create a new node and index it
	Node& n = m_indexedNodes[key];
	n.value = item;
	n.key = key;

	// update pointers
	if (m_back == NULL) {
		m_front = m_back = &n;
	} else {
		Node* p = m_back;
		m_back->next = &n;
		m_back = m_back->next;
		m_back->prev = p;
	}
}

template<typename Key, typename Object>
FastDeque<Key, Object>::Iterator::Iterator()
	: m_current(NULL)
{
}

template<typename Key, typename Object>
FastDeque<Key, Object>::Iterator::Iterator(FastDeque<Key, Object>::Node* cur)
	: m_current(cur)
{
}

template<typename Key, typename Object>
typename FastDeque<Key, Object>::Iterator& FastDeque<Key, Object>::Iterator::operator-- (
	int)
{
	if (m_current && m_current->prev) {
		m_current = m_current->prev;
	} else {
		m_current = NULL;
	}
	return *this;
}

template<typename Key, typename Object>
typename FastDeque<Key, Object>::Iterator& FastDeque<Key, Object>::Iterator::operator++ (
	int)
{
	if (m_current && m_current->next) {
		m_current = m_current->next;
	} else {
		m_current = NULL;
	}
	return *this;
}

template<typename Key, typename Object>
Object& FastDeque<Key, Object>::Iterator::operator* ()
{
	return m_current->value;
}
