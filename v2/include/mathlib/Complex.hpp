#pragma once

#include "Rational.hpp"
#include <ostream>

class Complex {
  private:
	Rational _real;
	Rational _imag;

  public:
	Complex(Rational r = 0.0, Rational i = 0.0);
	Rational real() const;
	Rational imag() const;

	bool operator==(const Complex &other) const;
};

std::ostream &operator<<(std::ostream &out, const Complex &c);
