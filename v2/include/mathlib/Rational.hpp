#pragma once

#include <cstdint>
#include <string>

class Rational {
  private:
	std::int64_t _numerator;
	std::int64_t _denominator;

  public:
	Rational(std::int64_t numerator = 0, std::int64_t denominator = 1);
	Rational(std::string decimal);

	std::int64_t numerator() const;
	std::int64_t denominator() const;
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

std::int64_t checked_add(std::int64_t a, std::int64_t b);
std::int64_t checked_sub(std::int64_t a, std::int64_t b);
std::int64_t checked_mul(std::int64_t a, std::int64_t b);
std::int64_t checked_div(std::int64_t a, std::int64_t b);

std::ostream &operator<<(std::ostream &out, const Rational &r);
