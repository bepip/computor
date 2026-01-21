#pragma once

#include "computor.hpp"

#include <ostream>

class Complex {
  private:
	double _real;
	double _imag;

  public:
	Complex(double r = 0.0, double i = 0.0);
	double real() const;
	double imag() const;

	bool operator==(const Complex &other) const;
};

std::ostream &operator<<(std::ostream &out, const Complex &c);
