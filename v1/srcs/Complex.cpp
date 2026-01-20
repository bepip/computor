#include "../includes/Complex.hpp"

Complex::Complex() :
	_real(0),
	_imag(0) {}

Complex::Complex(const Complex &c) :
	_real(c._real),
	_imag(c._imag) {}

Complex::Complex(double real, double imag) {
	_real = real;
	_imag = imag;
}

Complex::~Complex() {}

const Complex &Complex::operator=(const Complex &c) {
	if (this == &c) {
		return *this;
	}
	_real = c._real;
	_imag = c._imag;
	return *this;
}

double Complex::real() const {
	return _real;
}

double Complex::imag() const {
	return _imag;
}

std::ostream &operator<<(std::ostream &out, const Complex &c) {
	out << "(" << c.real() << ", " << c.imag() << ")";
	return out;
}
