#include <iostream>

void func1()
{
	class A {
	public:
		void const_f() const {
			std::cout << "const f()\n";
		}

		void f() {
			std::cout << "f()\n";
		}
	};

	// behave like a reference
	{
		A * const a = new A(); // const pointer to A (read 'const a')
		a->const_f();

		a->f();
		// a = new A();  // compile error
	}

	// behaves like a normal variable but can call only const functions
	{
		const A * a = new A(); // pointer to a const A (read 'const A')
		a->const_f();

		// a->f(); // compile error
		a = new A();
	}
	
	std::cout << std::endl;
}

int main()
{
	func1();

	return 0;
}
