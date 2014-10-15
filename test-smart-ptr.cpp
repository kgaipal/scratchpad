// class A
// {
// 	int m1;
// 	void func1()
// 	{
// 	}

// 	class A_nested
// 	{
// 		void func2()
// 		{
// 			func1();
// 			A::m1 = 1;
// 		}
// 	};
// };

// int main()
// {
// 	A a;
// 	return 0;
// }

#include <iostream>
#include <memory>
#include <unordered_map>
#include <queue>

class A
{
public:
	A(int i)
		:m_i(i)
	{
		std::cout << "A(" << m_i << ")\n";
	}

	~A()
	{
		std::cout << "~A(" << m_i << ")\n";
	}

	void print()
	{
		std::cout << "A::print(" << m_i << ")\n";
	}

private:
	int m_i;
};

std::queue< std::shared_ptr<A> > gQueue;
std::unordered_map< int, std::shared_ptr<A> > gUoMap;
std::unordered_map< int, std::unique_ptr<A> > gUoMap2;

std::shared_ptr<A> dequeue()
{
	std::cout << gQueue.front().use_count() << std::endl;
	if (gQueue.empty()) {
		return std::shared_ptr<A>();
	}

	std::shared_ptr<A> b = gQueue.front();

	std::cout << gQueue.front().use_count() << std::endl;
	gQueue.pop();
	std::cout << b.use_count() << std::endl;
	return b;
}

bool addA(int key, const std::shared_ptr<A>& a)
{
	if (gUoMap.find(key) != gUoMap.end()) {
		return false;	// cant overwrite
	}

	std::cout << a.use_count() << std::endl;
	gUoMap[key] = a;
	std::cout << a.use_count() << std::endl;
	return true;
}

int main()
{
	std::shared_ptr<A> a(new A(99));
	std::cout << (addA(0, a)?"true":"false") << std::endl;
	std::cout << gUoMap[0].use_count() << std::endl;

	// std::shared_ptr<A> a(new A(1));
	// std::cout << a.use_count() << std::endl;
	// gQueue.push(a);
	// std::cout << gQueue.front().use_count() << std::endl;
	// std::cout << a.use_count() << std::endl;
	// a.reset(new A(2));
	// std::cout << gQueue.front().use_count() << std::endl;
	// std::cout << a.use_count() << std::endl;

	// std::cout << "before dequeue()\n";
	// {
	// 	std::shared_ptr<A> b = dequeue();
	// 	std::cout << b.use_count() << std::endl;
	// }
	// std::cout << "after dequeue()\n";

	// std::cout << "before return 0;\n";

	return 0;
}
