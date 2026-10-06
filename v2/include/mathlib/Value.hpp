
#pragma once

#include "../../include/mathlib/Complex.hpp"
#include "Matrix.hpp"
#include "Rational.hpp"
#include <variant>

class Value {

  public:
	std::variant<Rational, Complex,  Matrix/*,
											 * Vector,*/>
		data;

	void print() const;
};
