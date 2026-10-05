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
	const auto &real = c.real();
	const auto &imag = c.imag();

	const bool has_real = real != Rational(0);
	const bool has_imag = imag != Rational(0);

	if (has_real || !has_imag) {
		out << c.real();
	}

	if (!has_imag) {
		return out;
	}

	const bool positive = c.imag() >= Rational(0);
	const Rational magnitude = positive ? imag : -imag;

	if (has_real) {
		out << (positive ? " + " : " - ");
	} else if (!positive) {
		out << "-";
	}

	if (magnitude == 1) {
		out << "i";
	} else {
		out << magnitude << "i";
	}
	return out;
}

bool Complex::operator==(const Complex &other) const {
	// return math::near_equal(_real, other._real) && math::near_equal(_imag,
	// other._imag);
	return _real == other._real && _imag == other._imag;
}
