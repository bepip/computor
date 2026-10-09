#include "../../include/mathlib/Rational.hpp"
#include <charconv>
#include <cstdint>
#include <iostream>
#include <limits>
#include <numeric>
#include <ostream>
#include <stdexcept>
#include <string>

Rational::Rational(std::int64_t numerator, std::int64_t denominator) :
	_numerator(numerator),
	_denominator(denominator) {
	normalize();
}

Rational::Rational(std::string decimal) {
	auto dot_pos = decimal.find(".");
	std::size_t decimals_len = 0;
	if (dot_pos != std::string::npos) {
		decimals_len = decimal.size() - dot_pos - 1;
		decimal.erase(dot_pos, 1);
	}
	std::int64_t value;
	auto [ptr, ec] =
		std::from_chars(decimal.data(), decimal.data() + decimal.size(), value);
	if (ec == std::errc::invalid_argument || ptr != decimal.data() + decimal.size()) {
		throw std::logic_error("Rational: invalid numeric lexeme");
	}

	if (ec == std::errc::result_out_of_range) {
		throw std::overflow_error("Rational value is too large");
	}

	_numerator = value;
	_denominator = 1;
	for (std::size_t i = 0; i < decimals_len; ++i) {
		if (_denominator > std::numeric_limits<std::int64_t>::max() / 10) {
			throw std::overflow_error("Rational denominator is too large");
		}
		_denominator *= 10;
	}
	normalize();
}

std::int64_t Rational::numerator() const {
	return _numerator;
}

std::int64_t Rational::denominator() const {
	return _denominator;
}

double Rational::to_double() const {
	return static_cast<double>(_numerator) / static_cast<double>(_denominator);
}

// TODO: check for overflows
Rational Rational::operator+(const Rational &rhs) const {
	std::int64_t g = std::gcd(_denominator, rhs._denominator);
	//  num = (_numerator * rhs._denominator + rhs._numerator * _denominator) / g;
	std::int64_t num = checked_div(checked_add(checked_mul(_numerator, rhs._denominator),
											   checked_mul(rhs._numerator, _denominator)),
								   g);
	// std::int64_t deno = (_denominator * rhs._denominator) / g;
	std::int64_t deno = checked_div(checked_mul(_denominator, rhs._denominator), g);
	return {num, deno};
}

Rational Rational::operator-(const Rational &rhs) const {
	int64_t g = std::gcd(_denominator, rhs._denominator);
	auto left_multiplier = rhs._denominator / g;
	auto right_multiplier = _denominator / g;
	std::int64_t num = _numerator * left_multiplier - rhs._numerator * right_multiplier;
	std::int64_t deno = _denominator * left_multiplier;
	return {num, deno};
}

Rational Rational::operator*(const Rational &rhs) const {
	auto n1 = _numerator;
	auto d1 = _denominator;
	auto n2 = rhs._numerator;
	auto d2 = rhs._denominator;
	auto g1 = std::gcd(_numerator, rhs._denominator);
	auto g2 = std::gcd(rhs._numerator, _denominator);
	n1 /= g1;
	d2 /= g1;
	n2 /= g2;
	d1 /= g2;

	return {checked_mul(n1, n2), checked_mul(d1, d2)};
}

Rational Rational::operator/(const Rational &rhs) const {
	Rational inverse(rhs._denominator, rhs._numerator);

	return *this * inverse;
}

// TODO: write function body
Rational Rational::operator%(const Rational &rhs) const {
	if (_denominator != 1 || rhs._denominator != 1) {
		throw std::domain_error("Modulo requires integer operands");
	}

	if (rhs._numerator == 0) {
		throw std::domain_error("Modulo by zero");
	}
	return {_numerator % rhs._numerator};
}

Rational Rational::operator^(const Rational &rhs) const {
	if (rhs._denominator != 1 || rhs._numerator < 0) {
		throw std::domain_error("Power requires a positive integer");
	}
	std::int64_t num = 1;
	std::int64_t den = 1;
	for (std::int64_t i = 0; i < rhs._numerator; ++i) {
		num = checked_mul(num, _numerator);
		den = checked_mul(den, _denominator);
	}
	return {num, den};
}

Rational &Rational::operator+=(const Rational &rhs) {
	*this = *this + rhs;
	return *this;
}

Rational &Rational::operator-=(const Rational &rhs) {
	*this = *this - rhs;
	return *this;
}

Rational &Rational::operator*=(const Rational &rhs) {
	*this = *this * rhs;
	return *this;
}

Rational &Rational::operator/=(const Rational &rhs) {
	*this = *this / rhs;
	return *this;
}

Rational Rational::operator-() const {
	return {checked_sub(0, _numerator), _denominator};
}

bool Rational::operator==(const Rational &rhs) const {
	return _numerator == rhs._numerator && _denominator == rhs._denominator;
}

bool Rational::operator!=(const Rational &rhs) const {
	return !(*this == rhs);
}

bool Rational::operator<(const Rational &rhs) const {
	return checked_mul(_numerator, rhs._denominator) <
		   checked_mul(rhs._numerator, _denominator);
}

bool Rational::operator<=(const Rational &rhs) const {
	return *this == rhs || *this < rhs;
}

bool Rational::operator>(const Rational &rhs) const {
	return !(*this <= rhs);
}

bool Rational::operator>=(const Rational &rhs) const {
	return !(*this < rhs);
}

std::ostream &operator<<(std::ostream &out, const Rational &r) {
	if (r.denominator() == 1) {
		return out << r.numerator();
	}
	return out << r.numerator() << "/" << r.denominator();
}

void Rational::normalize() {
	if (_denominator == 0) {
		throw std::domain_error("Rational: zero denomintor");
	}
	if (_numerator == 0) {
		_denominator = 1;
		return;
	}
	if (_denominator < 0) {
		_numerator = checked_mul(_numerator, -1);
		_denominator = checked_mul(_denominator, -1);
	}

	const auto divisor = std::gcd(_numerator, _denominator);

	_numerator = checked_div(_numerator, divisor);
	_denominator = checked_div(_denominator, divisor);
}

std::int64_t checked_add(std::int64_t a, std::int64_t b) {
	std::int64_t result;
	if (__builtin_add_overflow(a, b, &result)) {
		throw std::overflow_error("Rational addition overflow");
	}
	return result;
	// WARNING: if 42 compiler does not have compiler builtins
	// constexpr auto MIN = std::numeric_limits<std::int64_t>::min();
	// constexpr auto MAX = std::numeric_limits<std::int64_t>::max();
	//
	// if (a > 0 && b > 0 && a > MAX - b) {
	// 	throw std::overflow_error("Rational addition overflow");
	// }
	// if (a < 0 && b < 0 && a < MIN - b) {
	// 	throw std::overflow_error("Rational addition overflow");
	// }
	// return a + b;
}

std::int64_t checked_sub(std::int64_t a, std::int64_t b) {
	std::int64_t result;
	if (__builtin_sub_overflow(a, b, &result)) {
		throw std::overflow_error("Rational subtraction overflow");
	}
	return result;
	// WARNING: if 42 compiler does not have compiler builtins
	// constexpr auto MIN = std::numeric_limits<std::int64_t>::min();
	// constexpr auto MAX = std::numeric_limits<std::int64_t>::max();
	//
	// if (b < 0 && a > MAX + b) {
	// 	throw std::overflow_error("Integer subtraction overflow");
	// }
	// if (b > 0 && a < MIN + b) {
	// 	throw std::overflow_error("Integer subtraction overflow");
	// }
	//
	// return a - b;
}

std::int64_t checked_mul(std::int64_t a, std::int64_t b) {
	std::int64_t result;
	if (__builtin_mul_overflow(a, b, &result)) {
		throw std::overflow_error("Rational multiplication overflow");
	}
	return result;
	// WARNING: if 42 compiler does not have compiler builtins
	// constexpr auto MIN = std::numeric_limits<std::int64_t>::min();
	// constexpr auto MAX = std::numeric_limits<std::int64_t>::max();
	// if (a > 0) {
	// 	if ((b > 0 && a > MAX / b) || (b < 0 && a < MIN / b)) {
	// 		throw std::overflow_error("Integer multiplication overflow");
	// 	}
	// } else if (a < 0) {
	// 	if ((b < 0 && a > MAX / b) || (b > 0 && a < MIN / b)) {
	// 		throw std::overflow_error("Integer multiplication overflow");
	// 	}
	// }
	// return a * b;
}

std::int64_t checked_div(std::int64_t a, std::int64_t b) {
	constexpr auto MIN = std::numeric_limits<std::int64_t>::min();

	if (b == 0) {
		throw std::domain_error("Rational division by zero");
	}
	if (a == MIN && b == -1) {
		throw std::overflow_error("Rational division overflow");
	}
	return a / b;
}
