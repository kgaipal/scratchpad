#include <iostream>


#define SIZE 10

void func1()
{
	auto* p  = new int[SIZE];

	for (unsigned i = 0; i < SIZE; i++) {
		// every alternate
		p[i] = i;
		i++;
		p[i] = i;
	}
	for (unsigned i = 0; i < SIZE; i++) {
		// every alternate
		std::cout << p[i] << " ";
	}
}


int main()
{
	func1();
}
