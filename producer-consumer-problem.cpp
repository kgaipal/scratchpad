// Producer Consumer problem using semaphores


#include <cstdlib>
#include <iostream>
#include <stdexcept>

class CircularBuffer
{
public:
	CircularBuffer() : m_items(0), m_begin(0), m_end(0) {}

	bool empty() const { return m_items == 0; }
	bool full() const { return m_items == MAX; }

	int deque()
	{
		if (empty()) {
			throw new std::runtime_error("buffer under run");
		}

		const int item = m_buffer[m_begin];
		m_items--;

		m_begin = (m_begin + 1) % MAX;
		return item;
	}

	void enque(int item)
	{
		if (full()) {
			throw new std::runtime_error("buffer over run");
		}

		m_buffer[m_end] = item;
		m_items++;

		m_end = (m_end + 1) % MAX;
	}

private:
	static const int MAX = 10;

	unsigned int m_items;	// keep a count of elements curently in circular buffer

	int m_buffer[MAX];
	unsigned int m_begin;	// non-empty slot where item can be removed from
	unsigned int m_end;	// empty available slot where new item can be inserted
};

class Stack
{
public:
	Stack() : m_pos(-1) {}

	bool isEmpty() const { return (m_pos < 0); }
	bool isFull() const  { return (m_pos >= MAX); }

	void push(int item)
	{
		if (isFull()) {
			throw new std::runtime_error("buffer over run");
		}

		// Mutex m(MAX);
		m_buffer[++m_pos] = item;
	}

	int pop()
	{
		if (isEmpty()) {
			throw new std::runtime_error("buffer under run");
		}

		// Mutex m(MAX);
		return m_buffer[m_pos--];
	}

private:
	static const int MAX = 10;

	int m_buffer[MAX];
	int m_pos;
};

class Thread
{
public:
	Thread()
	{
		// set up the thread data
	}

	virtual ~Thread()
	{
	}


	void sleep()
	{
	}

	void notify()
	{
	}

	virtual void run() = 0;
};

unsigned int g_chars = 0, g_space = MAX;

class Producer : public Thread
{
public:
	Producer(Stack& buffer) : m_buffer(buffer) {}

	// keep inserting some random numbers
	void run()
	{
		while(true) {
			wait(g_space);

			int produce = rand() % 10;
			m_buffer.enque(produce);
			std::cout << "Producer: " << produce << "\n";

			signal(g_chars);
		}
	}

private:
	CircularBuffer& m_buffer;
};

class Consumer : public Thread
{
public:
	Consumer(Stack& buffer) : m_buffer(buffer) {}

	// keep removing
	void run()
	{
		while(true) {
			wait(g_chars);
			std::cout << "Consumer: " << m_buffer.deque() << "\n";
			signal(g_space);
		}
	}

private:
	CircularBuffer& m_buffer;
};


int main()
{
	Stack buffer;
	{
		buffer.push(2);
		buffer.push(4);
		buffer.push(-1);
	}

	// 1 Producer and few Consumers: Producer saves his produce in a buffer and prints
	// it and Consumer removes an item from that buffer and print it

	Producer p(buffer);
	Consumer c1(buffer);
	Consumer c2(buffer);

	// start all
	p.run();
	c1.run();
	c2.run();

	sleep();
	return 0;
}
