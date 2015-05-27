#include <iostream>

void func1()
{
	class A
	{
	public:
		A(int i) : mi(i) { }
		int valueI() const { return mi; }

	private:
		int mi;		
	};
	
	class B
	{
	public:
		B(int i) : ma(new A(i)) {}
		A* operator->() const { return ma; }
		A& operator*() const { return *ma; }
	
	private:
		A* ma;
	};

	B b(8);
	std::cout << b->valueI();
	std::cout << (*b).valueI();
	std::cout << (*b).valueI();
}

int main()
{

	func1();
	return 0;
}
