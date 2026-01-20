#pragma once

#include <ostream>

class Complex {
  private:
	double _real;
	double _imag;

  public:
	Complex();
	Complex(const Complex &c);
	Complex(double real, double imag);
	~Complex();

	const Complex &operator=(const Complex &c);

	double real() const;
	double imag() const;
};

std::ostream &operator<<(std::ostream &out, const Complex &c);
