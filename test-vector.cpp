// comparing size, capacity and max_size
// compile & run: g++ -std=c++11 test-vector.cpp && ./a.out

#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>


void func1()
{
	std::vector<int> myvector;

	myvector.reserve(10001);
	// set some content in the vector:
	for (int i=0; i<10000; i++) myvector.push_back(i);

	std::cout << "size: " << (int) myvector.size() << '\n';
	std::cout << "capacity: " << (int) myvector.capacity() << '\n';
	std::cout << "max_size: " << (int) myvector.max_size() << '\n';
}

void func2()
{
	std::vector<int> v{ 3, 1, 4, 6, 0, 10};

	auto item = std::find(v.begin(), v.end(), 6);
	auto d = std::distance(v.begin(), item);
	std::cout << "pos of 6 should be 3 but is " << d << '\n';

	item = std::find(v.begin(), v.end(), 10);
	d = std::distance(v.begin(), item);
	std::cout << "pos of 10 should be 5 but is " << d << '\n';

	item = std::find(v.begin(), v.end(), 3);
	d = std::distance(v.begin(), item);
	std::cout << "pos of 3 should be ??? but is " << d << '\n';
}

class Point
{
public:
	Point(int a, int b)
		: _a(a), _b(b)
		{
		}

	int a() const { return _a; }
	int b() const { return _b; }

	std::string str() const
		{
			std::stringstream ss;
			ss << "(" << _a << "," << _b << ")";
			return ss.str();
		}

	bool operator==(const Point& other) const
		{
			std::cout << "comparing " << str() << " with " << other.str() << "\n";
			return a() == other.a() && b() == other.b();
		}

private:
	int _a;
	int _b;
};

void func3(const Point& point)
{
	std::vector<Point> v = {
		Point(1, -3), Point(1, 0), Point(1, 2),
		Point(2, -3), Point(2, 0), Point(2, 2),
		Point(3, -3), Point(3, 0), Point(3, 2),
	};

	auto p = std::find(v.begin(), v.end(), point);
	if (p != v.end()) {
		std::cout << "found!\n";
	} else {
		std::cout << "==failed\n";
	}
}

void test_swap()
{

	class Swap
	{
	public:
		Swap(int m): mmember(m) {
			std::cout << "Swap(" << member() << ")" << std::endl;
		}

		~Swap() {
			std::cout << "~Swap(" << member() << ")" << std::endl;
		}

		Swap(const Swap& other) {
			std::cout << "Swap(Swap& " << other.member() << ")" << std::endl;
			mmember = other.member();
		}

		int member() const { return mmember; }
	private:
		int mmember;

	};

	std::vector<Swap> vt = {
		Swap(1), Swap(2), Swap(3)
	};

	std::cout << "\n==swap now==" << std::endl << std::endl;

	std::vector<Swap> vtSwap;
	vt.swap(vtSwap);

	std::cout << "old:";
	for (auto &i : vt) {
		std::cout << "\t" << i.member();
	}

	std::cout << "\nnew:";
	for (auto &i : vtSwap) {
		std::cout << "\t" << i.member();
	}

	std::cout << "\n==swap end==" << std::endl << std::endl;
}

int main()
{
	// func1();
	// func2();
	// func3(Point(2,9));
	test_swap();
}
