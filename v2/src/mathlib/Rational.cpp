#include "../../include/mathlib/Rational.hpp"
#include <charconv>
#include <cstdint>
#include <iostream>
#include <limits>
#include <numeric>
#include <ostream>
#include <stdexcept>
#include <string>

Rational::Rational(std::intmax_t numerator, std::intmax_t denominator) :
	numerator(numerator),
	denominator(denominator) {
	normalize();
}

Rational::Rational(std::string decimal) {
	auto dot_pos = decimal.find(".");
	std::size_t decimals_len = 0;
	if (dot_pos != std::string::npos) {
		decimals_len = decimal.size() - dot_pos - 1;
		decimal.erase(dot_pos, 1);
	}
	std::intmax_t value;
	auto [ptr, ec] =
		std::from_chars(decimal.data(), decimal.data() + decimal.size(), value);
	if (ec == std::errc::invalid_argument || ptr != decimal.data() + decimal.size()) {
		throw std::logic_error("Rational: invalid numeric lexeme");
	}

	if (ec == std::errc::result_out_of_range) {
		throw std::overflow_error("Rational value is too large");
	}

	numerator = value;
	denominator = 1;
	for (std::size_t i = 0; i < decimals_len; ++i) {
		if (denominator > std::numeric_limits<std::intmax_t>::max() / 10) {
			throw std::overflow_error("Rational denominator is too large");
		}
		denominator *= 10;
	}
	normalize();
}

std::intmax_t Rational::get_numerator() const {
	return numerator;
}

std::intmax_t Rational::get_denominator() const {
	return denominator;
}

double Rational::to_double() const {
	return static_cast<double>(numerator) / static_cast<double>(denominator);
}

// TODO: replace all maths double to rational in all math files
// check for overflows
Rational Rational::operator+(const Rational &rhs) const {
	unsigned long g = std::gcd(denominator, rhs.denominator);
	std::intmax_t num = (numerator * rhs.denominator + rhs.numerator * denominator) / g;
	std::intmax_t deno = denominator * rhs.denominator / g;
	return {num, deno};
}

Rational Rational::operator-(const Rational &rhs) const {
	unsigned long g = std::gcd(denominator, rhs.denominator);
	auto left_multiplier = rhs.denominator / g;
	auto right_multiplier = denominator / g;
	std::intmax_t num = numerator * left_multiplier - rhs.numerator * right_multiplier;
	std::intmax_t deno = denominator * left_multiplier;
	return {num, deno};
}

Rational Rational::operator*(const Rational &rhs) const {
	auto n1 = numerator;
	auto d1 = denominator;
	auto n2 = rhs.numerator;
	auto d2 = rhs.denominator;
	auto g1 = std::gcd(numerator, rhs.denominator);
	auto g2 = std::gcd(rhs.numerator, denominator);
	n1 /= g1;
	d2 /= g1;
	n2 /= g2;
	d1 /= g2;

	return {n1 * n2, d1 * d2};
}

Rational Rational::operator/(const Rational &rhs) const {
	Rational inverse(rhs.denominator, rhs.numerator);

	return *this * inverse;
}

// TODO: write function body
Rational Rational::operator%(const Rational &rhs) const {
	(void)rhs;
	return {};
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
	return {-numerator, denominator};
}

bool Rational::operator==(const Rational &rhs) const {
	return numerator == rhs.numerator && denominator == rhs.denominator;
}

bool Rational::operator!=(const Rational &rhs) const {
	return !(*this == rhs);
}

bool Rational::operator<(const Rational &rhs) const {
	return numerator * rhs.denominator < rhs.numerator * denominator;
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
	out << r.get_numerator() << " / " << r.get_denominator();
	return out;
}

void Rational::normalize() {
	if (denominator == 0) {
		throw std::domain_error("Rational: zero denomintor");
	}
	if (numerator == 0) {
		denominator = 1;
		return;
	}
	if (denominator < 0) {
		numerator *= -1;
		denominator *= -1;
	}

	auto divisor = std::gcd(numerator, denominator);

	numerator /= divisor;
	denominator /= divisor;
}

bool Rational::add_overflow() const {
	return {};
}

bool Rational::sub_overflow() const {
	return {};
}

bool Rational::mul_overflow() const {
	return {};
}

bool Rational::div_overflow() const {
	return {};
}
