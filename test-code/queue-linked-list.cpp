
class Queue
{
public:
	Queue()
		: m_begin(nullptr), m_last(nullptr), m_length(0)
	{ }

	~Queue() {
		while (curr != nullptr) {
			delete curr;
			curr = curr->prev;
		}
	}

	bool isEmpty() const {
		return (m_length == 0);
	}

	unsigned size() const {
		return m_length;
	}

	void enqueue(void* data) {
		QItem* item = new QItem();
		item->item = data;

		if (isEmpty()) {
			m_begin = m_last = item;
		} else {
			m_last->next = item;
			m_last->prev = m_last;
			m_last = m_last->next;
		}
		m_length++;
	}

	void* deque() {
		if (isEmpty()) {
			return nullptr;
		}

		void* retVal = m_last->item;

		m_last = m_last->prev;
		delete m_last->next;
		m_last->next = nullptr;
		m_length--;

		return retVal;
	}

private:
	struct QItem {
		QItem()
			: next(nullptr), prev(nullptr), item(nullptr)
		{ }

		QItem* next;
		QItem* prev;
		void* item;
	};

	// any implementation for queue (vector or linkedlist[x])
	QItem* m_begin;
	QItem* m_last;
	unsigned m_length;
};
