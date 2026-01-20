#pragma once

#include <ostream>

struct Complex {
	double real;
	double imag;

	constexpr Complex(double r = 0.0, double i = 0.0) :
		real(r),
		imag(i) {};
};

inline std::ostream &operator<<(std::ostream &out, const Complex &c) {
	if (c.imag == 0)
		return out << c.real;
	if (c.imag < 0)
		return out << c.real << " - " << -c.imag << "i";
	return out << c.real << " + " << c.imag << "i";
}
