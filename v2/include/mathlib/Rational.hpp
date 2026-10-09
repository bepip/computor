#pragma once

#include <cstdint>
#include <string>

class Rational {
  private:
	std::intmax_t _numerator;
	std::intmax_t _denominator;

  public:
	Rational(std::intmax_t numerator = 0, std::intmax_t denominator = 1);
	Rational(std::string decimal);

	std::intmax_t numerator() const;
	std::intmax_t denominator() const;
	double to_double() const;

	Rational operator+(const Rational &rhs) const;
	Rational operator-(const Rational &rhs) const;
	Rational operator*(const Rational &rhs) const;
	Rational operator/(const Rational &rhs) const;
	Rational operator%(const Rational &rhs) const;
	Rational operator^(const Rational &rhs) const;

	Rational &operator+=(const Rational &rhs);
	Rational &operator-=(const Rational &rhs);
	Rational &operator*=(const Rational &rhs);
	Rational &operator/=(const Rational &rhs);

	Rational operator-() const;

	bool operator==(const Rational &rhs) const;
	bool operator!=(const Rational &rhs) const;
	bool operator<(const Rational &rhs) const;
	bool operator<=(const Rational &rhs) const;
	bool operator>(const Rational &rhs) const;
	bool operator>=(const Rational &rhs) const;

  private:
	void normalize();
};

std::intmax_t checked_add(std::intmax_t a, std::intmax_t b);
std::intmax_t checked_sub(std::intmax_t a, std::intmax_t b);
std::intmax_t checked_mul(std::intmax_t a, std::intmax_t b);
std::intmax_t checked_div(std::intmax_t a, std::intmax_t b);

std::ostream &operator<<(std::ostream &out, const Rational &r);
