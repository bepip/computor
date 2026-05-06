
#pragma once

#include "../../include/mathlib/Complex.hpp"
#include <iostream>
#include <variant>

class Value {

  public:
	std::variant<double, Complex /*,
											 * Matrix,
											 * Vector,
											 * Rational*/>
		data;

	struct Visitor {
		void operator()(double d) const { std::cout << "double: " << d << std::endl; }

		void operator()(Complex c) const { std::cout << "Complex: " << c << std::endl; }
	};

	void print() const;
};
