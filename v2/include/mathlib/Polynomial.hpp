#pragma once

#include "Rational.hpp"
#include <map>
#include <utility>

class Polynomial {
  private:
	std::map<std::uint64_t, Rational> _terms;

	[[nodiscard]]
	Polynomial lead() const;
	[[nodiscard]]
	Polynomial lead_div(const Polynomial &divisor) const;
  public:
	void add_term(std::uint64_t exponent, const Rational &coefficient,
				  bool is_sub = false);
	Rational term(std::uint64_t exponent) const;
	[[nodiscard]]
	Polynomial operator+(const Polynomial &rhs) const;
	[[nodiscard]]
	Polynomial operator-(const Polynomial &rhs) const;
	[[nodiscard]]
	Polynomial operator*(const Polynomial &rhs) const;
	[[nodiscard]]
	std::pair<Polynomial, Polynomial> divmod(const Polynomial &divisor) const;
	[[nodiscard]]
	Polynomial pow(std::uint64_t exponent) const;
	[[nodiscard]]
	bool is_zero() const;
	[[nodiscard]]
	std::uint64_t degree() const;
	const std::map<std::uint64_t, Rational> &terms() const;
};
