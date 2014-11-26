#include <iostream>

void func1()
{
	// class A;
	// auto manipulateI = [&] (A &a) {
	// 	a.m_i = 9;
	// };

	// class A
	// {
	// public:
	// 	A()
	// 	: m_i(-1)
	// 	{
	// 	}

	// 	int printI() const { return m_i; }

	// 	friend void manipulateI(A& a);

	// protected:
	// 	int m_i;
	// };


	// class B : public A
	// {
	// public:
	// 	B()
	// 	: A()
	// 	{
	// 		A::m_i = -2;
	// 	}
	// };

	// A a;
	// std::cout << a.printI() << std::endl;
	// manipulateI(a);
	// std::cout << a.printI() << std::endl;

	// B b;
	// std::cout << b.printI() << std::endl;
	// manipulateI(b);
	// std::cout << b.printI() << std::endl;
}

void func2()
{
	class A	{ int i; };
	class B : virtual public A { int i; };
	class C : virtual public A { int i; };

	class D : public B, public C
	{
	public:
		virtual ~D()
		{
		}
	private:
		int i;

	};

	D d;
	std::cout << sizeof(d) << std::endl;
}

int main()
{
	// func1();
	func2();

	return 0;
}
