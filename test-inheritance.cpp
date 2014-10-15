#include <iostream>

class A
{
public:
	A()
	: m_i(-1)
	{ }

	int printI() const { return m_i; }

	friend void manipulateI(A& a);

protected:
	int m_i;
};

void manipulateI(A &a)
{
	a.m_i = 9;
};


class B : public A
{
public:
	B()
		: A()
		{ A::m_i = -2;}

};

int main()
{
	A a;
	std::cout << a.printI() << std::endl;
	manipulateI(a);
	std::cout << a.printI() << std::endl;

	B b;
	std::cout << b.printI() << std::endl;
	manipulateI(b);
	std::cout << b.printI() << std::endl;
	return 0;
}
