// Compile with g++ --std=c++11 test-template.cpp

#include <iostream>

template<typename T>
void func_template(const T& a, const T& b)
{
	const T c = (a > b ? a : b);
	std::cout << c << std::endl;
}

void func2()
{
	{
		int a = 5, b = 0;
		func_template<int>(++a, b);
		func_template<int>(++a, b+10);
	}
	// {
	// 	float a = 5.0, b = 0.0;
	// 	func_template<float>(++a, b);
	// 	func_template<float>(++a, b+10);
	// }
}

int main()
{
	func2();

	return 0;
}
