#pragma once

#include "Rational.hpp"
#include <ostream>

class Complex {
  private:
	Rational _real;
	Rational _imag;

  public:
	explicit Complex(Rational r = {1, 0}, Rational i = {1, 0});
	Rational real() const;
	Rational imag() const;

	Complex operator+(const Complex &rhs) const;
	Complex operator-(const Complex &rhs) const;
	Complex operator*(const Complex &rhs) const;
	Complex operator/(const Complex &rhs) const;

	Complex &operator+=(const Complex &rhs);
	Complex &operator-=(const Complex &rhs);
	Complex &operator*=(const Complex &rhs);
	Complex &operator/=(const Complex &rhs);

	Complex operator-() const;

	bool operator==(const Complex &rhs) const;
	bool operator!=(const Complex &rhs) const;
};

std::ostream &operator<<(std::ostream &out, const Complex &c);
