#include "fraction.h"

#include <stdexcept>
#include <sstream>

void swap(int& a, int& b)
{
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}

unsigned int gcd(unsigned int a, unsigned int b)
{
	// borrowed from gcc
	while (b != 0) {
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}

Fraction::Fraction(int numer, int denom)
	: m_numerator(numer)
	, m_denominator(denom)
{
	if (d() == 0) {
		throw std::runtime_error(
			"invalid fraction: denominator cant be zero");
	}

	// simplify
	reduceFactors();
}

void Fraction::reduceFactors()
{
	// sign reduction
	// propagate sign from denominator to numerator
	// -a/-b is a/b
	// a/-b is -a/b
	if (d() < 0) {
		m_denominator *= -1;
		m_numerator *= -1;
	}

	// equal factors
	if (n() == d()) {
		m_numerator = m_denominator = 1;
	}

	// multiples reduction
	// TODO: for efficiency rather calculate gcd() before displaying?
	int g = 0;		// no loss of precision
	if (n() < 0) {
		g = gcd(-1 * n(), d());
	} else {
		g = gcd(n(), d());
	}
	if (g > 1) {
		m_numerator /= g;
		m_denominator /= g;
	}
}

Fraction::Fraction(const Fraction& other)
	: m_numerator(other.n())
	, m_denominator(other.d())
{
}

const std::string Fraction::toString() const
{
	std::stringstream ss;
	if (isZero() || isOne() || d() == 1) {
		ss << n();
	} else {
		ss << n() << "/" << d();
	}

	return ss.str();
}

const Fraction Fraction::operator+(const Fraction& other) const
{
	// equal denominators
	if (d() == other.d()) {
		return Fraction(n() + other.n(), d());
	}

	// unequal denominators
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

	// equal denominators
	if (d() == other.d()) {
		return Fraction(n() - other.n(), d());
	}

	// unequal denominators
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
	if (other.isZero()) {
		throw std::runtime_error("cant divided by zero");
	}

	return Fraction(n() * other.d(), d() * other.n());
}

bool Fraction::operator==(const Fraction& other) const
{
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
