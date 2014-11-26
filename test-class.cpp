#include <typeinfo>
#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>

class A_static
{
public:
	void printI()
	{
		std::cout << "A::" << s_i << "\n";
	}

	static void setI(int i)
	{
		s_i = i;
	}

private:
	static int s_i;
};

int A_static::s_i = 0;

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

	virtual void abstract() = 0;

protected:
	int m_i;
};

class B : public A
{
public:
	B(int i, int j)
		: A(i)
		, m_j(j)
	{
		std::cout << "B(" << A::m_i << "," << m_j << ")\n";
	}

	virtual ~B()
	{
		std::cout << "~B(" << A::m_i << "," << m_j << ")\n";
	}

	void abstract()
	{
		std::cout << "B::abstract(" << A::m_i << "," << m_j << ")\n";
	}

private:
	int m_j;
};

class C : public A
{
public:
	C(int i, int j)
		: A(i)
		, m_j(j)
	{
		std::cout << "C(" << A::m_i << "," << m_j << ")\n";
	}

	virtual ~C()
	{
		std::cout << "~C(" << A::m_i << "," << m_j << ")\n";
	}

	void abstract()
	{
		std::cout << "C::abstract(" << A::m_i << "," << m_j << ")\n";
	}

private:
	int m_j;
};

void func1()
{
	{
		A_static::setI(7);
	}

	A_static a;
	a.printI();
	A_static::setI(99);
	a.printI();
}

void func2()
{
	std::unordered_map< int, std::unique_ptr<A> > um;

	um[0] = std::unique_ptr<A>(new B(2,99));
	um[1].reset(new C(-2,-99));
}

void func3()
{
	std::vector< std::unique_ptr<A> > vt;

	vt.push_back(std::unique_ptr<A>(new B(2,99)));
	vt.push_back(std::unique_ptr<A>(new C(-2,-99)));

	std::unique_ptr<A> x(new C(-1,-100));
	vt.push_back(std::move(x));

	for (size_t i = 0; i < vt.size(); i++) {

		A* a = vt[i].get();
		std::cout << "-\n";
		if (typeid(*a) == typeid(B)) {
			vt[i]->abstract();
		} else if (typeid(*a) == typeid(C)) {
			vt[i]->abstract();
		}
	}
}

void func4()
{
	class X
	{
	public:
		// explicit X(int a)
		X(int a)
		{
		}
	};

	// X x_obj = 1;	// error because 'explicit' is used
	X x_obj = 1;		// implicit conversion allowed
}

namespace nmspc1
{
	class X
	{
	public:
		X();
		virtual ~X() = 0; // forcing abstractness
	};

	X::X() {}
	X::~X() { std::cout << "~X()\n";}

	class A : public X { public: virtual ~A() { std::cout << "~A()\n";}};

	void func1()
	{
		A* a = new A;
		delete a;
	}
};

void operatorOverloading()
{
	class A
	{
	public:
		A(bool set) : mi(set) { }
		bool getI() const { return mi; }
		bool operator&&(bool i) const { return (mi && i);	}
		bool operator&&(const A& other) const { return (mi && other.getI()); }
	private:
		int mi;
	};

	A a(false), b(false);
	std::cout << (a && b && true) << "\n";
}

void emptyClass()
{
	class A {};
	class B {};
	class C {};
	class D {};
	class Dx {char c; char x;};

	std::cout << sizeof(A) << ","
		  << sizeof(B) << ","
		  << sizeof(C) << ","
		  << sizeof(D) << ","
		  << sizeof(Dx) << std::endl;
}

int main()
{
	// func1();
	// func2();
	// func3();
	// func4();

	// nmspc1::X* x = new nmspc1::X; // error: cant abstract class
	// nmspc1::func1();
	// operatorOverloading();
	emptyClass();
	return 0;
}
