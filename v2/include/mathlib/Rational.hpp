#pragma once

#include <cstdint>
#include <string>

class Rational {
  private:
	std::intmax_t numerator;
	std::intmax_t denominator;

  public:
	Rational(std::intmax_t numerator = 0, std::intmax_t denominator = 0);
	Rational(std::string decimal);

	std::intmax_t get_numerator() const;
	std::intmax_t get_denominator() const;
	double to_double() const;

	Rational operator+(const Rational &rhs) const;
	Rational operator-(const Rational &rhs) const;
	Rational operator*(const Rational &rhs) const;
	Rational operator/(const Rational &rhs) const;
	Rational operator%(const Rational &rhs) const;

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
	bool add_overflow() const;
	bool sub_overflow() const;
	bool mul_overflow() const;
	bool div_overflow() const;
};

std::ostream &operator<<(std::ostream &out, const Rational &r);
