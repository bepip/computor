#include "../../include/mathlib/Complex.hpp"
#include "../../include/mathlib/math_utils.hpp"

Complex::Complex(double r, double i) :
	_real(math::normalize_zero(r)),
	_imag(math::normalize_zero(i)) {};

double Complex::real() const {
	return _real;
}

double Complex::imag() const {
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
	return math::near_equal(_real, other._real) && math::near_equal(_imag, other._imag);
}
