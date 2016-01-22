// compile and run as :
// g++ -std=c++11 -g -Wall ../fraction.h  main.cpp   && ./a.out

#include <iostream>

#include "../fraction.h"
#include "../algebraic-expressions.h"


template<typename T>
void compute(const Fraction<T>& f1, const Fraction<T>& f2)
{
	try {
		std::cout << "\n-------------\n";
		std::cout << "f1: " << f1.toString();
		std::cout << "\nf2: " << f2.toString();
		std::cout << std::endl;

		std::cout << "\nf1 + f2 = " << (f1 + f2).toString();
		std::cout << "\nf1 - f2 = " << (f1 - f2).toString();
		std::cout << "\nf1 * f2 = " << (f1 * f2).toString();
		std::cout << "\nf1 / f2 = " << (f1 / f2).toString();

		std::cout << "\nf1 == f2? " << (f1 == f2);
		std::cout << "\nf1 != f2? " << (f1 != f2);
		std::cout << "\nf1 < f2 ? " << (f1 < f2);
		std::cout << "\nf1 > f2 ? " << (f1 > f2);

	} catch (std::exception& e) {
		std::cout << "\nerror:" << e.what();
	}
	std::cout << std::endl;
}

template<typename T>
void display(const Fraction<T>& f)
{
	try {
		std::cout << "f: " << f.toString();

	} catch (std::exception& e) {
		std::cout << "\nerror:" << e.what();
	}
	std::cout << std::endl;
}

int main()
{
	AlgebraicExpression a, d;
	display(Fraction<AlgebraicExpression>(a, d));

	display(Fraction<int>(3,4));
	display(Fraction<int>(7,7));
	display(Fraction<int>(14,7));
	display(Fraction<int>(7,-14));
	display(Fraction<int>(13,-39));
	display(Fraction<int>(39,-13));

	compute(Fraction<int>(1,3), Fraction<int>(2,4));
	compute(Fraction<int>(1,2), Fraction<int>(1,1));
	compute(Fraction<int>(1,2), Fraction<int>(1,2));
	compute(Fraction<int>(1,2), Fraction<int>(1,-2));
	compute(Fraction<int>(1,2), Fraction<int>(-1,-2));
	compute(Fraction<int>(-1,2), Fraction<int>(0,-2));
	compute(Fraction<int>(-1,2), Fraction<int>(0,-2));
	compute(Fraction<int>(-1), Fraction<int>(5));
}
