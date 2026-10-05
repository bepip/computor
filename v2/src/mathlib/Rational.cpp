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
	std::intmax_t value;
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
		if (_denominator > std::numeric_limits<std::intmax_t>::max() / 10) {
			throw std::overflow_error("Rational denominator is too large");
		}
		_denominator *= 10;
	}
	normalize();
}

std::intmax_t Rational::numerator() const {
	return _numerator;
}

std::intmax_t Rational::denominator() const {
	return _denominator;
}

double Rational::to_double() const {
	return static_cast<double>(_numerator) / static_cast<double>(_denominator);
}

// TODO: replace all maths double to rational in all math files
// check for overflows
Rational Rational::operator+(const Rational &rhs) const {
	unsigned long g = std::gcd(_denominator, rhs._denominator);
	std::intmax_t num =
		(_numerator * rhs._denominator + rhs._numerator * _denominator) / g;
	std::intmax_t deno = _denominator * rhs._denominator / g;
	return {num, deno};
}

Rational Rational::operator-(const Rational &rhs) const {
	unsigned long g = std::gcd(_denominator, rhs._denominator);
	auto left_multiplier = rhs._denominator / g;
	auto right_multiplier = _denominator / g;
	std::intmax_t num = _numerator * left_multiplier - rhs._numerator * right_multiplier;
	std::intmax_t deno = _denominator * left_multiplier;
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

	return {n1 * n2, d1 * d2};
}

Rational Rational::operator/(const Rational &rhs) const {
	Rational inverse(rhs._denominator, rhs._numerator);

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
	return {-_numerator, _denominator};
}

bool Rational::operator==(const Rational &rhs) const {
	return _numerator == rhs._numerator && _denominator == rhs._denominator;
}

bool Rational::operator!=(const Rational &rhs) const {
	return !(*this == rhs);
}

bool Rational::operator<(const Rational &rhs) const {
	return _numerator * rhs._denominator < rhs._numerator * _denominator;
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
		out << r.numerator();
	} else {
		out << r.numerator() << " / " << r.denominator();
	}
	return out;
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
		_numerator *= -1;
		_denominator *= -1;
	}

	auto divisor = std::gcd(_numerator, _denominator);

	_numerator /= divisor;
	_denominator /= divisor;
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
