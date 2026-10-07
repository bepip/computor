
#pragma once

#include "../../include/mathlib/Complex.hpp"
#include "Matrix.hpp"
#include "Rational.hpp"
#include <variant>

class Value {

  public:
	std::variant<Rational, Complex, Matrix /*,Vector,*/> data;

	void print() const;

	template <typename T> bool is() const { return std::holds_alternative<T>(data); }

	template <typename T> const T &get() const { return std::get<T>(data); }
};
