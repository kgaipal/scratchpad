#include "fraction.h"

#include <stdexcept>
#include <sstream>

// reduces given fraction to simpler terms
template<typename T>
void Fraction<T>::reduce(T& numerator, T& denominator)
{
	// no-op
}

// computes greatest common divisor
int gcd(int a, int b)
{
	if (a < 0) {
		a *= -1;
	}

	if (b < 0) {
		b *= -1;
	}

	// borrowed from gcc
	while (b != 0) {
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}

// specialization(integer) for reducing fraction to simpler terms
template<>
void Fraction<int>::reduce(int& numerator, int& denominator)
{
	// multiples reduction
	const int g = gcd(numerator, denominator);

	if (g != 1/*1 is everybody's divisor*/) {
		numerator /= g;
		denominator /= g;
	}
}

template<typename T>
Fraction<T>::Fraction(T numer, T denom)
	: m_numerator(numer)
	, m_denominator(denom)
{
	if (d() == 0) {
		throw std::runtime_error(
			"invalid fraction: denominator cant be zero");
	}

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

	// simplify terms
	reduce(m_numerator, m_denominator);
}

template<typename T>
Fraction<T>::Fraction(const Fraction<T>& other)
	: m_numerator(other.n())
	, m_denominator(other.d())
{
}

template<typename T>
const std::string Fraction<T>::toString() const
{
	std::stringstream ss;
	if (d() == 0 || n() == d() || d() == 1) {
		ss << n();
	} else {
		ss << n() << "/" << d();
	}

	return ss.str();
}

template<typename T>
const Fraction<T> Fraction<T>::operator+(const Fraction<T>& other) const
{
	// equal denominators
	if (d() == other.d()) {
		return Fraction(n() + other.n(), d());
	}

	// unequal denominators, make denominators equal and then add
	return Fraction((n() * other.d()) + (d() * other.n()), d() * other.d());
}

template<typename T>
const Fraction<T> Fraction<T>::operator-(const Fraction<T>& other) const
{
	// equal denominators
	if (d() == other.d()) {
		return Fraction(n() - other.n(), d());
	}

	// unequal denominators, make denominators equal and then subtract
	return Fraction((n() * other.d()) - (d() * other.n()), d() * other.d());
}

template<typename T>
const Fraction<T> Fraction<T>::operator*(const Fraction<T>& other) const
{
	return Fraction(n() * other.n(), d() * other.d());
}

template<typename T>
const Fraction<T> Fraction<T>::operator/(const Fraction<T>& other) const
{
	return Fraction(n() * other.d(), d() * other.n());
}

template<typename T>
bool Fraction<T>::operator==(const Fraction<T>& other) const
{
	if (d() == other.d()) {
		return n() == other.n();
	}

	// otherwise make denominators equal and then compare numerators
	return ((n() * other.d()) == (d() * other.n()));
}

template<typename T>
bool Fraction<T>::operator!=(const Fraction<T>& other) const
{
	return !(*this == other);
}

template<typename T>
bool Fraction<T>::operator>(const Fraction<T>& other) const
{
	if (d() == other.d()) {
		return n() > other.n();
	}

	// otherwise make denominators equal and then compare numerators
	return ((n() * other.d()) > (d() * other.n()));
}

template<typename T>
bool Fraction<T>::operator<(const Fraction<T>& other) const
{
	// if same denominators then only compare numerators
	if (d() == other.d()) {
		return n() < other.n();
	}

	// otherwise make denominators equal and then compare numerators
	return ((n() * other.d()) < (d() * other.n()));
}
