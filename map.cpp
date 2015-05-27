#include <map>
#include <iostream>

class Key
{
public:
	Key(int data) : m_data(data) { std::cout << "\t" << m_data; }
	Key(const Key& other) { this->m_data = other.m_data; std::cout << "\t" << m_data; }

	bool operator<(const Key& other) const
	{
		return this->m_data < other.m_data;
	}

	void reset(int newData) { m_data = newData; }

private:
	int m_data;
};


class Value
{
public:
	Value(int data) : m_data(data) {}

	bool operator<(const Value& other) const
	{
		return this->m_data < other.m_data;
	}

private:
	int m_data;
};

int main()
{

	// std::map<Key*, int> x;
	// for (int i = 3; i < 10; i++) {
	// 	x[new Key(i)] = i;
	// }


	std::map<Key, int> x;
	Key k(0);
	for (int i = 3; i < 10; i++) {
		k.reset(i);
		x[k] = i;
	}

	return 0;
}
