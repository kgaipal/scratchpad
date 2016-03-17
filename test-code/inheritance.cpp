#include <iostream>

void func1()
{
	// class A;
	// auto manipulateI = [&] (A &a) {
	//	a.m_i = 9;
	// };

	// class A
	// {
	// public:
	//	A()
	//	: m_i(-1)
	//	{
	//	}

	//	int printI() const { return m_i; }

	//	friend void manipulateI(A& a);

	// protected:
	//	int m_i;
	// };


	// class B : public A
	// {
	// public:
	//	B()
	//	: A()
	//	{
	//		A::m_i = -2;
	//	}
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

void func3()
{
	class Base {
	public:
		virtual void print() {
			std::cout << "base::print()" << std::endl;
		}
	};


	class DerivedA : public Base {
	public:
		void print() {
			std::cout << "derivedA::print()" << std::endl;
		}
	};

	class DerivedB : public Base {
	public:
		void print() {
			std::cout << "derivedB::print()" << std::endl;
		}
	};

	class User {
	public:
		User(Base& base)
			: mbase(base) {
		}

		void print() {
			mbase.print();
		}
	private:
		Base& mbase;
	};

	DerivedA da;
	User usera(da);
	usera.print();

	DerivedB db;
	User userb(db);
	userb.print();
}


namespace enum_inheritance
{
	class Base {
	public:
		struct statusCode {
			static const unsigned eStarting;
			static const unsigned eFailed;
		};

	};

	class Derived : public Base {
	public:
		struct statusCodeEx : public statusCode {
			static const unsigned eCertFailed;
		};
	};

	const unsigned Base::statusCode::eStarting = 0;
	const unsigned Base::statusCode::eFailed = 1;
	const unsigned Derived::statusCodeEx::eCertFailed = 3;

} // namespace enum_inheritance

void func4()
{
	using namespace enum_inheritance;

	Derived d;
}

int main()
{
	// func1();
	// func2();
	// func3();
	func4();

	return 0;
}
