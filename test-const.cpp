#include <iostream>

int foo()
{
	int var = 4;
	return var;
}

int main()
{
	// const int& s = foo();

	// std::cout << s << std::endl;

	// int N = 5;
	// for (int m = -5; m < N; m++) {
	// 	std::cout << m%N << " ";
	// }

	// std::cout << -7%8;

	long l_type = -1;
	std::cout << l_type << " size:" << sizeof(l_type) << std::endl;

	int i_type = -2;
	std::cout << i_type << " size:" << sizeof(i_type) << std::endl;

	return 0;
}
