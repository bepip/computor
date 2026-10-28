#pragma once

#include "Rational.hpp"
#include <map>

class Polynomial {
  private:
	std::map<std::uint64_t, Rational> _terms;

  public:
	void add_term(std::uint64_t exponent, const Rational &coefficient);
	Rational term(std::uint64_t exponent) const;
	[[nodiscard]]
	Polynomial operator+(const Polynomial &rhs) const;
	[[nodiscard]]
	Polynomial operator-(const Polynomial &rhs) const;
	[[nodiscard]]
	Polynomial operator*(const Polynomial &rhs) const;
	[[nodiscard]]
	Polynomial pow(std::uint64_t exponent) const;
	[[nodiscard]]
	bool is_zero() const;
	const std::map<std::uint64_t, Rational> &terms() const;
};
