#include "../includes/Complex.hpp"

Complex::Complex(double r, double i) :
	_real(normalizeZero(r)),
	_imag(normalizeZero(i)) {};

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
	return _real == other._real && _imag == other._imag;
}
