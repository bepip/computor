
#pragma once

#include "../../include/mathlib/Complex.hpp"
#include "Matrix.hpp"
#include "Rational.hpp"
#include <variant>

class Value {

  public:
	Value(const Value &) = default;
	Value &operator=(const Value &) = default;
	std::variant<Rational, Complex, Matrix /*,Vector,*/> data;

	void print() const;
	void println() const;

	template <typename T> bool is() const { return std::holds_alternative<T>(data); }

	template <typename T> const T &get() const { return std::get<T>(data); }
};
