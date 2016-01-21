#include "fraction.h"

#include <stdexcept>
#include <iostream>

Fraction::Fraction(int numer, int denom)
	: m_numerator(numer)
	, m_denominator(denom)
{
	if (denominator() == 0) {
		throw std::runtime_error(
			"invalid fraction: denominator cant be zero");
	}

	if (numerator() == denominator()) {
		m_numerator = m_denominator = 1;
	}

	// TODO: simplify fraction here
	// reduce();
}

Fraction::Fraction(const Fraction& other)
	: m_numerator(other.numerator())
	, m_denominator(other.denominator())
{
}

void Fraction::display() const
{
	if (numerator() == 0 || numerator() == denominator()) {
		std::cout << numerator();
	} else {
		std::cout << numerator() << "/" << denominator();
	}
}

const Fraction Fraction::operator+(const Fraction& other) const
{
	if (denominator() == other.denominator()) {
		return Fraction(
			numerator() + other.numerator(),
			denominator());
	}

	// make denom equal
	return Fraction(
		(numerator() * other.denominator())
		+ (denominator() * other.numerator()),
		other.denominator() * denominator());
}

const Fraction Fraction::operator-(const Fraction& other) const
{
	// negate other fraction if this is zero
	if (numerator() == 0) {
		return Fraction(Fraction(-1) * other);
	}

	// nothing to subtract if other fraction is zero
	if (other.numerator() == 0) {
		return *this;
	}

	if (denominator() == other.denominator()) {
		return Fraction(
			numerator() - other.numerator(),
			denominator());
	}

	// make denom equal
	return Fraction(
		(numerator() * other.denominator())
		- (denominator() * other.numerator()),
		other.denominator() * denominator());
}

const Fraction Fraction::operator*(const Fraction& other) const
{
	return Fraction(
		numerator() * other.numerator(),
		denominator() * other.denominator());
}

const Fraction Fraction::operator/(const Fraction& other) const
{
	return Fraction(
		numerator() * other.denominator(),
		denominator() * other.numerator());
}

bool Fraction::operator==(const Fraction& other) const
{
	return (numerator() == other.numerator()
		&& denominator() == other.denominator());
}

bool Fraction::operator!=(const Fraction& other) const
{
	return !(*this == other);
}

bool Fraction::operator>(const Fraction& other) const
{
	return false;
}

bool Fraction::operator<(const Fraction& other) const
{
	return false;
}
