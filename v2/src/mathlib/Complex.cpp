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

Complex Complex::conjugate() const {
	return {_real, -_imag};
}

Rational Complex::squared_modulus() const {
	return Rational(_real * _real + _imag * _imag);
}

Complex Complex::operator+(const Complex &rhs) const {
	return {_real + rhs._real, _imag + rhs._imag};
}

Complex Complex::operator-(const Complex &rhs) const {
	return {_real - rhs._real, _imag - rhs._imag};
}

Complex Complex::operator*(const Complex &rhs) const {
	const auto real = _real * rhs._real - _imag * rhs._imag;
	const auto imag = _real * rhs._imag + _imag * rhs._real;
	return {real, imag};
}

Complex Complex::operator/(const Complex &rhs) const {
	const auto real_num = _real * rhs._real + _imag * rhs._imag;
	const auto imag_num = _imag * rhs._real - _real * rhs._imag;
	const auto denominator = rhs.squared_modulus();
	return {real_num / denominator, imag_num / denominator};
}

Complex &Complex::operator+=(const Complex &rhs) {
	*this = *this + rhs;
	return *this;
}

Complex &Complex::operator-=(const Complex &rhs) {
	*this = *this - rhs;
	return *this;
}

Complex &Complex::operator*=(const Complex &rhs) {
	*this = *this * rhs;
	return *this;
}

Complex &Complex::operator/=(const Complex &rhs) {
	*this = *this / rhs;
	return *this;
}

Complex Complex::operator-() const {
	return {-_real, -_imag};
}

bool Complex::operator==(const Complex &other) const {
	return _real == other._real && _imag == other._imag;
}

bool Complex::operator!=(const Complex &rhs) const {
	return !(*this == rhs);
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
