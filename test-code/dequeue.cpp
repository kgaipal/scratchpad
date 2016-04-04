#include <iostream>
#include <memory>
#include <deque>
#include <unordered_map>
#include <algorithm>

#include "Bomgar/FastDeque.h"

class A
{
public:
	A(int i)
		:m_i(i)
	{
		std::cout << "A(" << m_i << ")\n";
	}

	virtual ~A()
	{
		std::cout << "~A(" << m_i << ")\n";
	}

	int getI() const { return m_i; }

	friend bool operator== (const A& a, const A& b)
	{
		std::cout << a.m_i << "==" << b.m_i << "?\n";
		return a.m_i == b.m_i;
	}

protected:
	int m_i;
};

// bool dequePred(const std::shared_ptr<A>& a)
// {
//	if (a.get()) {
//		return (a.get()->getI() == 0);
//	}

//	return false;
// }

// void deque_noptr()
// {
//	std::deque<A> dq;

//	for (int i = 1; i < 10; i++) {
//		dq.push_back(A(i));
//	}

//	for (auto it = dq.begin(); it != dq.end() ; it++) {
//		std::cout << it->getI() << " ";
//	}
//	std::cout << std::endl;

//	A sItem(10);

//	auto it = std::find(dq.begin(), dq.end(), sItem);
//	std::cout << sItem.getI()
//		  << (it != dq.end()? " found" : " failed") << std::endl;
//	it++;

//	if (it != dq.end()) {
//		std::cout << "next: " << it->getI() << std::endl;
//	}

//	sItem = A(11);

//	it = std::find(dq.begin(), dq.end(), sItem);
//	std::cout << sItem.getI()
//		  << (it != dq.end()? " found" : " failed") << std::endl;
// }

bool find_in_deque(const std::deque< std::shared_ptr<A> >& dq, const A& sItem)
{
	auto it = std::find_if(dq.begin(), dq.end(),
		[sItem] (const std::shared_ptr<A>& a) {
			return (a.get() && a.get()->getI() == sItem.getI());
		});

	return it != dq.end();
}

// void deqeue_withptr()
// {
//	std::deque< std::shared_ptr<A> > dq;

//	std::shared_ptr<A> a;
//	for (int i = 1; i < 10; i++) {
//		dq.push_back( std::shared_ptr<A>(new A(i)) );
//	}

//	for (auto it = dq.begin(); it != dq.end() ; it++) {
//		if (it->get()) {
//			std::cout << it->get()->getI();
//		} else {
//			std::cout << "x";
//		}
//		std::cout << " ";
//	}
//	std::cout << std::endl;

//	A sItem(3);
//	std::cout << sItem.getI()
//		  << (find_in_deque(dq, sItem)? " found" : " failed") << std::endl;

//	// if (it->get()) {
//	//	std::cout << "next: " << (it->get())->getI() << std::endl;
//	// }

//	sItem = A(10);
//	std::cout << sItem.getI()
//		  << (find_in_deque(dq, sItem)? " found" : " failed") << std::endl;

//	sItem = A(9);
//	std::cout << sItem.getI()
//		  << (find_in_deque(dq, sItem)? " found" : " failed") << std::endl;
// }

void fast_deque()
{
	FastDeque< unsigned int, std::shared_ptr<A> > dq;

	std::shared_ptr<A> a;
	for (int i = 1; i < 9; i++) {
		dq.push_back( i, std::shared_ptr<A>(new A(i)) );
	}

	// iterate
	for (auto it = dq.begin(); it != dq.end(); it++) {
		std::cout << (*it)->getI() << " ";
	}
	std::cout << std::endl;

	dq.push_back(-1, std::shared_ptr<A>(new A(-1)));
	dq.pop_front();
	dq.push_back(99, std::shared_ptr<A>(new A(99)));
	dq.push_back(-99, std::shared_ptr<A>(NULL));

	// iterate
	for (auto it = dq.begin(); it != dq.end(); it++) {
		std::cout << (*it)->getI() << " ";
	}
	std::cout << std::endl;

	std::cout << (dq.find(9) != dq.end()? "9 found" : "9 failed") << std::endl;
	std::cout << (dq.find(0) != dq.end()? "0 found" : "0 failed") << std::endl;
	std::cout << (dq.find(4) != dq.end()? "4 found" : "4 failed") << std::endl;
	std::cout << (dq.find(2) != dq.end()? "2 found" : "2 failed") << std::endl;
}

void test_deque_size()
{
	std::deque<int> dq(100);

	std::cout << "\nsize:" << dq.size();
	std::cout << "\nmax size:" << dq.max_size();
}

int main()
{
	// deqeue_withptr();
	// deque_noptr();
	// fast_deque();

	std::cout << sizeof(unsigned int);
	test_deque_size();

	std::cout << std::endl;
	return 0;
}
