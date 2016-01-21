// Jan 20, 2016
// Kshitij Gaipal

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

#include <string>

class Fraction
{
public:
	Fraction(int numer, int denom=1);
	Fraction(const Fraction& other);

	void display() const;
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

	inline bool isZero() const { return n() == 0; }
	inline bool isOne() const { return (n() == d()) == 1; }

	inline int n() const { return m_numerator; }
	inline int d() const { return m_denominator; }

	int m_numerator;
	int m_denominator;
};
