#include "fraction.h"

#include <stdexcept>
#include <iostream>

Fraction::Fraction(int numer, int denom)
	: m_numerator(numer)
	, m_denominator(denom)
{
	if (d() == 0) {
		throw std::runtime_error(
			"invalid fraction: denominator cant be zero");
	}

	if (n() == d()) {
		m_numerator = m_denominator = 1;
	}

	// TODO: simplify fraction here
	// reduce();
}

Fraction::Fraction(const Fraction& other)
	: m_numerator(other.n())
	, m_denominator(other.d())
{
}

void Fraction::display() const
{
	if (isZero() || isOne()) {
		std::cout << n() << std::endl;
	} else {
		std::cout << n() << "/" << d() << std::endl;
	}
}

const Fraction Fraction::operator+(const Fraction& other) const
{
	if (d() == other.d()) {
		return Fraction(n() + other.n(), d());
	}

	// make denominators equal
	return Fraction((n() * other.d()) + (d() * other.n()), other.d() * d());
}

const Fraction Fraction::operator-(const Fraction& other) const
{
	// negate other fraction if this is zero
	if (isZero()) {
		return Fraction(Fraction(-1) * other);
	}

	// nothing to subtract if other fraction is zero
	if (other.isZero()) {
		return *this;
	}

	if (d() == other.d()) {
		return Fraction(n() - other.n(), d());
	}

	// make denominators equal
	return Fraction(
		(n() * other.d()) - (d() * other.n()),
		other.d() * d());
}

const Fraction Fraction::operator*(const Fraction& other) const
{
	return Fraction(n() * other.n(), d() * other.d());
}

const Fraction Fraction::operator/(const Fraction& other) const
{
	return Fraction(n() * other.d(), d() * other.n());
}

bool Fraction::operator==(const Fraction& other) const
{
	// if same denominators then only compare numerators
	if (d() == other.d()) {
		return n() == other.n();
	}

	// otherwise make denominators equal and then compare numerators
	return ((n() * other.d()) == (other.n() * d()));
}

bool Fraction::operator!=(const Fraction& other) const
{
	return !(*this == other);
}

bool Fraction::operator>(const Fraction& other) const
{
	// if same denominators then only compare numerators
	if (d() == other.d()) {
		return n() > other.n();
	}

	// otherwise make denominators equal and then compare numerators
	return ((n() * other.d()) > (other.n() * d()));
}

bool Fraction::operator<(const Fraction& other) const
{
	// if same denominators then only compare numerators
	if (d() == other.d()) {
		return n() < other.n();
	}

	// otherwise make denominators equal and then compare numerators
	return ((n() * other.d()) < (other.n() * d()));
}
