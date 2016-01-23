// Jan 23, 2016
// Kshitij Gaipal


// Text verbatim from James.Lebak@mathworks.com:
// ---------------------------------------------
// I’m writing in regard to your application for a C++ software
// engineer position at MathWorks. We’ve received your application and
// are impressed with your credentials. As the next step in the
// process, I’d like to ask you to do the coding exercise described
// below. Once I’ve received your solution we can schedule a phone
// interview to discuss your solution and your qualifications for and
// interest in the position. If possible, please send me your solution
// by the close of business on Monday, 25 January 2016. If you need
// more time for some reason please let me know.

// Implement in C++ a Fraction class that supports the following
// operations: addition, subtraction, multiplication, division,
// equality/non-equality, greater than/less than, and display. The
// project should take on the order of several hours. If you have some
// ideas that would take longer to implement please write them down
// for discussion.

// Class represents a fraction and computes following mathematical
// operations on any given two such instances:
// 1. addition
// 2. subtraction
// 3. multiplication
// 4. division
// 5. equality/non-equality
// 6. greater than/less than

// --------------------------------------------

#ifndef _FRACTION_H_
#define _FRACTION_H_

#include <string>
#include <iostream>

// Note: Templatization for Fraction class below can be useful for
// non-integer fractions. For e.g. Algaebric expressions, radical
// numbers, etc can also be denominators/numerators in a fraction.
// (https://en.wikipedia.org/wiki/Fraction_%28mathematics%29#Algebraic_fractions).
// In such a case approriate class needs to implement various
// arithmetic operators of this class. Also these other types of data
// classes can implement their own reduce functions if necessary.
//
template<typename T>
class Fraction
{
public:
	Fraction(T numer, T denom=1/*if set, represent whole number*/);
	Fraction(const Fraction& other);

	inline void display() const { std::cout << toString() ; }
	const std::string toString() const;

	const Fraction operator+(const Fraction& other) const;
	const Fraction operator-(const Fraction& other) const;
	const Fraction operator*(const Fraction& other) const;
	const Fraction operator/(const Fraction& other) const;

	bool operator==(const Fraction& other) const;
	bool operator!=(const Fraction& other) const;
	bool operator>(const Fraction& other) const;
	bool operator<(const Fraction& other) const;

private:
	// util functions
	inline T n() const { return m_numerator; }
	inline T d() const { return m_denominator; }

	T m_numerator;
	T m_denominator;
};

#include "fraction.cpp"

#endif	// _FRACTION_H_
