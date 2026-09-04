#include "../../include/mathlib/Complex.hpp"

Complex::Complex(Rational r, Rational i) :
	// _real(math::normalize_zero(r)),
	// _imag(math::normalize_zero(i)) {};
	_real(r),
	_imag(i) {};

Rational Complex::real() const {
	return _real;
}

Rational Complex::imag() const {
	return _imag;
}

std::ostream &operator<<(std::ostream &out, const Complex &c) {
	if (c.imag() == 0)
		return out << c.real();
	if (c.imag() < 0)
		return out << c.real() << " - " << -c.imag() << "i";
	return out << c.real() << " + " << c.imag() << "i";
}

bool Complex::operator==(const Complex &other) const {
	// return math::near_equal(_real, other._real) && math::near_equal(_imag,
	// other._imag);
	return _real == other._real && _imag == other._imag;
}
