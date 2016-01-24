// compile and run as :
// g++ -std=c++11 -g -Wall ../fraction.h  main.cpp   && ./a.out

#include <iostream>
#include <map>
#include <vector>

#include "../fraction.h"
#include "../algebraic-expressions.h"

template<typename T>
struct Results {
	Fraction<T> expected;
	Fraction<T> actual;

	std::string error;

	Results(const Fraction<T>& e)
		: expected(e), actual(Fraction<T>(1))
	{}
};

template<typename T>
struct FractionData {
	const Fraction<T> f1;
	const Fraction<T> f2;

	std::map<std::string/*operator*/, Results<T>> results;

	FractionData(
		const Fraction<T>& f1,
		const Fraction<T>& f2,
		const std::map<std::string, Results<T>>& r)
		: f1(f1), f2(f2), results(r)
	{}
};

void compute(std::vector<FractionData<int>>& data)
{
	for (auto& d : data) {
		for (auto &r : d.results) {
			try {
				if (r.first == "+") {
					r.second.actual = d.f1 + d.f2;
				} else if (r.first == "-") {
					r.second.actual = d.f1 - d.f2;
				} else if (r.first == "*") {
					r.second.actual = d.f1 * d.f2;
				} else if (r.first == "/") {
					r.second.actual = d.f1 / d.f2;
				} else if (r.first == "<") {
					r.second.actual = (d.f1 < d.f2);
				} else if (r.first == ">") {
					r.second.actual = (d.f1 > d.f2);
				} else if (r.first == "!=") {
					r.second.actual = (d.f1 != d.f2);
				} else if (r.first == "==") {
					r.second.actual = (d.f1 == d.f2);
				}

			} catch (std::exception& e) {
				r.second.error = e.what();
			}
		}
	}
}

void display(std::vector<FractionData<int>>& data)
{
	for (auto& d : data) {
		for (auto &r : d.results) {
			if (r.second.expected != r.second.actual) {
				std::cout << d.f1.toString() << " "
					  << r.first << " "
					  << d.f2.toString() << " = "
					  << r.second.actual.toString();

				std::cout << " ; mismatch: '"
					  << r.second.error << "'";
			}
		}
	}
	std::cout << "\n";
}

int main()
{
	std::cout << "==== display only ====" << std::endl;

	// AlgebraicExpression a, d;
	// display(Fraction<AlgebraicExpression>(a, d));

	Fraction<int>(3,4).display();
	Fraction<int>(7,7).display();
	Fraction<int>(14,7).display();
	Fraction<int>(7,-14).display();
	Fraction<int>(13,-39).display();
	Fraction<int>(39,-13).display();

	std::cout << "==== compute only ====" << std::endl;
	std::vector<FractionData<int>> data;

	{
		FractionData<int> fd(
			Fraction<int>(1,2),
			Fraction<int>(1,2),
			std::map<std::string, Results<int> >({
				{"+", Results<int>(Fraction<int>(1,1))},
				{"-", Results<int>(Fraction<int>(0,1))},
				{"*", Results<int>(Fraction<int>(1,4))},
				{"/", Results<int>(Fraction<int>(1))},
				{"<", Results<int>(Fraction<int>(0))},
				{">", Results<int>(Fraction<int>(0))},
				{"==", Results<int>(Fraction<int>(1))},
				{"!=", Results<int>(Fraction<int>(0))},
			}));
		data.push_back(fd);
	}
	{
		FractionData<int> fd(
			Fraction<int>(1,3),
			Fraction<int>(2,4),
			std::map<std::string, Results<int> >({
				{"+", Results<int>(Fraction<int>(5,6))},
				{"-", Results<int>(Fraction<int>(-1,6))},
				{"*", Results<int>(Fraction<int>(1,6))},
				{"/", Results<int>(Fraction<int>(2,3))},
				{"<", Results<int>(Fraction<int>(1))},
				{">", Results<int>(Fraction<int>(0))},
				{"==", Results<int>(Fraction<int>(0))},
				{"!=", Results<int>(Fraction<int>(1))},
			}));
		data.push_back(fd);
	}
	{
		FractionData<int> fd(
			Fraction<int>(2,4),
			Fraction<int>(1,3),
			std::map<std::string, Results<int> >({
				{"+", Results<int>(Fraction<int>(5,6))},
				{"-", Results<int>(Fraction<int>(1,6))},
				{"*", Results<int>(Fraction<int>(1,6))},
				{"/", Results<int>(Fraction<int>(3,2))},
				{"<", Results<int>(Fraction<int>(0))},
				{">", Results<int>(Fraction<int>(1))},
				{"==", Results<int>(Fraction<int>(0))},
				{"!=", Results<int>(Fraction<int>(1))},
			}));
		data.push_back(fd);
	}
	{
		FractionData<int> fd(
			Fraction<int>(1,-2),
			Fraction<int>(1,2),
			std::map<std::string, Results<int> >({
				{"+", Results<int>(Fraction<int>(0))},
				{"-", Results<int>(Fraction<int>(-1))},
				{"*", Results<int>(Fraction<int>(-1,4))},
				{"/", Results<int>(Fraction<int>(-1))},
				{"<", Results<int>(Fraction<int>(1))},
				{">", Results<int>(Fraction<int>(0))},
				{"==", Results<int>(Fraction<int>(0))},
				{"!=", Results<int>(Fraction<int>(1))},
			}));
		data.push_back(fd);
	}
	{
		FractionData<int> fd(
			Fraction<int>(0,-1),
			Fraction<int>(1,2),
			std::map<std::string, Results<int> >({
				{"+", Results<int>(Fraction<int>(1,2))},
				{"-", Results<int>(Fraction<int>(-1,2))},
				{"*", Results<int>(Fraction<int>(0))},
				{"/", Results<int>(Fraction<int>(0))},
				{"<", Results<int>(Fraction<int>(1))},
				{">", Results<int>(Fraction<int>(0))},
				{"==", Results<int>(Fraction<int>(0))},
				{"!=", Results<int>(Fraction<int>(1))},
			}));
		data.push_back(fd);
	}
	{
		FractionData<int> fd(
			Fraction<int>(1,2),
			Fraction<int>(0,-1),
			std::map<std::string, Results<int> >({
				{"+", Results<int>(Fraction<int>(1,2))},
				{"-", Results<int>(Fraction<int>(1,2))},
				{"*", Results<int>(Fraction<int>(0))},
				{"/", Results<int>(Fraction<int>(0))}, // error
				{"<", Results<int>(Fraction<int>(0))},
				{">", Results<int>(Fraction<int>(1))},
				{"==", Results<int>(Fraction<int>(0))},
				{"!=", Results<int>(Fraction<int>(1))},
			}));
		data.push_back(fd);
	}
	{
		FractionData<int> fd(
			Fraction<int>(5),
			Fraction<int>(1),
			std::map<std::string, Results<int> >({
				{"+", Results<int>(Fraction<int>(6))},
				{"-", Results<int>(Fraction<int>(4))},
				{"*", Results<int>(Fraction<int>(5))},
				{"/", Results<int>(Fraction<int>(5))},
				{"<", Results<int>(Fraction<int>(0))},
				{">", Results<int>(Fraction<int>(1))},
				{"==", Results<int>(Fraction<int>(0))},
				{"!=", Results<int>(Fraction<int>(1))},
			}));
		data.push_back(fd);
	}
	{
		FractionData<int> fd(
			Fraction<int>(1),
			Fraction<int>(5),
			std::map<std::string, Results<int> >({
				{"+", Results<int>(Fraction<int>(6))},
				{"-", Results<int>(Fraction<int>(-4))},
				{"*", Results<int>(Fraction<int>(5))},
				{"/", Results<int>(Fraction<int>(1,5))},
				{"<", Results<int>(Fraction<int>(1))},
				{">", Results<int>(Fraction<int>(0))},
				{"==", Results<int>(Fraction<int>(0))},
				{"!=", Results<int>(Fraction<int>(1))},
			}));
		data.push_back(fd);
	}
	{
		FractionData<int> fd(
			Fraction<int>(-1,2),
			Fraction<int>(-1,2),
			std::map<std::string, Results<int> >({
				{"+", Results<int>(Fraction<int>(-1))},
				{"-", Results<int>(Fraction<int>(0))},
				{"*", Results<int>(Fraction<int>(1,4))},
				{"/", Results<int>(Fraction<int>(1))},
				{"<", Results<int>(Fraction<int>(0))},
				{">", Results<int>(Fraction<int>(0))},
				{"==", Results<int>(Fraction<int>(1))},
				{"!=", Results<int>(Fraction<int>(0))},
			}));
		data.push_back(fd);
	}

	compute(data);
	display(data);
}
