#include <iostream>

#include "../fraction.h"

void compute(const Fraction& f1, const Fraction& f2)
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

void display(const Fraction& f)
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
	display(Fraction(3,4));
	display(Fraction(7,7));
	display(Fraction(14,7));
	display(Fraction(7,-14));
	display(Fraction(13,-39));
	display(Fraction(39,-13));

	compute(Fraction(1,2), Fraction(1,1));
	compute(Fraction(1,2), Fraction(1,2));
	compute(Fraction(1,2), Fraction(1,-2));
	compute(Fraction(1,2), Fraction(-1,-2));
	compute(Fraction(-1,2), Fraction(0,-2));
	compute(Fraction(0,-2), Fraction(-1,2));
	compute(Fraction(-1), Fraction(5));
}
