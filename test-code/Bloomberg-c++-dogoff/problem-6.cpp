/**
6.  Implement a deque.  Think about what properties a deque must have.
 Implement it as a base class that can be extended and as a template.
In general, start thinking about what's underneath all the other STL
data types and how they work.

Sol: I have tried a templatized solution. Implemented three classes:

First a basic 'Deque' with access to elements from front and back and also clear the deque
if demanded.
Edit: I later realized after reading up other STL containers that I can avoid a copy of
item before popping by exposing iterators kind of references to my stored items like I did
in IterableDeque below. This way I never bother to make a copy and pop_*() functions can
just remove items and not returning anything and clients can access stored items using
iterators... much similar to STL deque.

Second an inheriting class 'DequePeek' which extends standard deque above and adds two
functions to peek if there is any data. Throws exception if tried on empty deque.

Third another inheriting class 'IterableDeque' which provides capability to iterate over
the deque just like a STL deque with iterators (here they are bidirectional and queue is
not searchable). No exception is thrown but can fail in dereferencing functions (left by
design just like STL iterators).

 */

template<typename T>
class Deque
{
public:
	Deque()
	 : head(nullptr)
	 , tail(nullptr)
	 , mItems(0)
	{
	}

	inline unsigned int size() const
	{
		return mItems;
	}

	inline bool empty() const
	{
		return (nItems == 0);
	}

	virtual ~Deque()
	{
		clear();
	}

	void clear()
	{
		// destroy each item manually
		while (!empty()) {
			pop_front(); // dtor for each 'node->data' will destory it
		}
	}

	void push_front(const T& item)
	{
		if (empty()) {
			tail = head = new Node(item); // first node
		} else {
			head->prev = new Node(item);
			head->prev->next = head;
			head = head->prev;
		}
		nItems++;
	}

	const T pop_back()
	{
		if (empty()) {
			throw std::runtime_error("cannot pop from empty deque");
		}

		Node* n = tail;
		tail = tail->prev;
		tail->next = nullptr;

		const T copy = n->data; // make a copy of the data item
		delete n;
		nItems--;
		return copy;	// edit: see note at the begining of the file.
	}

	void push_back(const T& item)
	{
		if (empty()) {
			tail = head = new Node(item); // first node
		} else {
			tail->next = new Node(item);
			tail->next->prev = tail;
			tail = tail->next;
		}
		nItems++;
	}

	const T pop_front()
	{
		if (empty()) {
			throw std::runtime_error("cannot pop from empty deque");
		}

		Node* n = head;
		head = head->next;
		head->prev = nullptr;

		const T copy = n->data; // make a copy of the data item
		delete n;
		nItems--;
		return copy;
	}

protected:
	inline const Node* front() const
	{
		return head;
	}

	inline const Node* back() const
	{
		return tail;
	}

	class Node
	{
	public:
		Node()
		 : prev(nullptr)
		 , next(nullptr)
		{
		}

		Node(const T& d)
		 : prev(nullptr)
		 , next(nullptr)
		 , data(d)
		{
		}

		Node* prev;
		T data;
		Node* next;
	};

private:
	Node* head;
	Node* tail;
	unsigned int mItems;
};

// a deque which will add two more functions which allow you to peek what is in the queue
// in the front or back
template <typename T>
class DequePeek : public Deque<T>
{
public:
	inline const T& peek_front() const
	{
		if (empty()) {
			throw std::runtime_error("no data to peek");
		}
		return front()->data;
	}

	inline const T& peek_back() const
	{
		if (empty()) {
			throw std::runtime_error("no data to peek");
		}
		return back()->data;
	}
};

// this class doesnt throw exception but can definitely fail if misused using ++ or --
// operators, to keep it simple no boundary checks
template <typename T>
class IterableDeque : public Deque<T>
{
public:
	class Iterator
	{
	public:
		Iterator()
		 : node(nullptr)
		{
		}

		Iterator& operator++()
		{
			node = node->next;
			return *this;
		}

		// callee should be able to modify the data if needed but certainly not
		// iterator itself, hence return a non-const reference to data
		T& operator*() const
		{
			return node->data;
		}

		Iterator& operator--()
		{
			node = node->prev;
			return *this;
		}

	private:
		Node* node;

		friend bool operator==(const Iterator& lhs, const Iterator& rhs)
		{
			return (lhs.node == rhs.node
				&& (lsh.node != nullptr && rhs.node != nullptr
				    lhs.node->data == rhs.node->data));
		}

		friend bool operator!=(const Iterator& lhs, const Iterator& rhs)
		{
			return !(lhs == rhs);
		}

		 // should be able to instantiate Iterator with a given node
		friend class IterableDeque;
		Iterator(Node* node)
		 : node(node)
		{
		}
	};

	inline Iterator begin() const
	{
		if (empty()) {
			return end();
		}
		return Iterator(front());
	}

	inline Iterator end() const
	{
		return Iterator(nullptr);
	}

	inline Iterator rbegin() const
	{
		if (empty()) {
			return end();
		}
		return Iterator(back());
	}

	inline Iterator rend() const
	{
		return Iterator(nullptr);
	}
};
