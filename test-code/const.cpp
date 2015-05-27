#include <iostream>

int foo()
{
	int var = 4;
	return var;
}

void func1()
{
	const int& s = foo();
	std::cout << s << std::endl;
}

void func2()
{
	int N = 5;
	for (int m = -5; m < N; m++) {
		std::cout << m%N << " ";
	}

	std::cout << -7%8;
}

void func3()
{
	long l_type = -1;
	std::cout << l_type << " size:" << sizeof(l_type) << std::endl;

	int i_type = -2;
	std::cout << i_type << " size:" << sizeof(i_type) << std::endl;
}

void func4()
{
	class A
	{
	public:
		void f1() const { ; }
		void f2() { ; }
	};

	A a;
	const A& a_ref = a;
	const A& aa_ref = a_ref;

	a.f1();
	a_ref.f1();
	aa_ref.f1();

	a.f2();
	// a_ref.f2();		// error: cant invoke non-const function
	// aa_ref.f2();		// error: cant invoke non-const function

	const A* const a_ptr = &a;
	a_ptr->f1();
	// a_ptr->f2();		// error: cant invoke non-const function from non-const ptr
}

int main()
{
	// func4();

	return 0;
}
