#include <iostream>

class AlgebraicExpression
{
public:
	AlgebraicExpression() {
	}

	AlgebraicExpression(int a, int b) {
	}
	
	AlgebraicExpression(int a) {
	}

	bool operator==(int) const {
		return false;	// TODO
	}

	bool operator!=(int) const {
		return false;	// TODO
	}

	AlgebraicExpression operator%(const AlgebraicExpression&) {
		return AlgebraicExpression();	// TODO
	}

	AlgebraicExpression& operator=(int) {
		return *this;	// TODO
	}

	bool operator<(int) const {
		return false;	// TODO
	}

	bool operator>(int) const {
		return false;	// TODO
	}

	AlgebraicExpression operator*=(int) const {
		return AlgebraicExpression();	// TODO
	}

	const AlgebraicExpression operator*(int) const {
		return AlgebraicExpression();	// TODO
	}

	const AlgebraicExpression operator/=(const AlgebraicExpression&) const {
		return AlgebraicExpression();	// TODO
	}

	bool operator==(const AlgebraicExpression&) const {
		return false;	// TODO
	}

	bool operator!=(const AlgebraicExpression&) const {
		return false;	// TODO
	}

	bool operator<(const AlgebraicExpression&) const {
		return false;	// TODO
	}

	bool operator>(const AlgebraicExpression&) const {
		return false;	// TODO
	}

	const AlgebraicExpression operator+(const AlgebraicExpression&) const {
		return AlgebraicExpression();	// TODO
	}

	const AlgebraicExpression operator-(const AlgebraicExpression&) const {
		return AlgebraicExpression();	// TODO
	}

	const AlgebraicExpression operator*(const AlgebraicExpression&) const {
		return AlgebraicExpression();	// TODO
	}

	const AlgebraicExpression operator/(const AlgebraicExpression&) const {
		return AlgebraicExpression();	// TODO
	}

	friend std::ostream& operator<<(
		std::ostream& os,
		const AlgebraicExpression&) {
		return os;
	}

	// TODO
};
