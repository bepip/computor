#include "../../include/mathlib/Polynomial.hpp"
#include <cstdint>
#include <limits>
#include <stdexcept>

void Polynomial::add_term(std::uint64_t exponent, const Rational &coefficient) {
	if (coefficient == Rational(0)) {
		return;
	}
	auto it = _terms.find(exponent);
	if (it == _terms.end()) {
		_terms.emplace(exponent, coefficient);
		return;
	}
	const Rational sum = coefficient + it->second;
	if (sum == Rational(0)) {
		_terms.erase(it);
	} else {
		it->second = sum;
	}
}

Rational Polynomial::term(std::uint64_t exponent) const {
	const auto it = _terms.find(exponent);
	return it == _terms.end() ? Rational(0) : it->second;
}

Polynomial Polynomial::operator+(const Polynomial &rhs) const {
	Polynomial p = *this;

	for (const auto &[exp, coef] : rhs._terms) {
		p.add_term(exp, coef);
	}
	return p;
}

Polynomial Polynomial::operator-(const Polynomial &rhs) const {
	Polynomial p = *this;

	for (const auto &[exp, coef] : rhs._terms) {
		auto it = p._terms.find(exp);
		if (it == p._terms.end()) {
			p.add_term(exp, -coef);
			continue;
		}
		const Rational diff = it->second - coef;
		if (diff == Rational(0)) {
			p._terms.erase(it);
		} else {
			it->second = diff;
		}
	}
	return p;
}

Polynomial Polynomial::operator*(const Polynomial &rhs) const {
	if (rhs.is_zero() || this->is_zero()) {
		return {};
	}

	Polynomial res;

	const std::uint64_t m = this->_terms.rbegin()->first;
	const std::uint64_t n = rhs._terms.rbegin()->first;

	if (std::numeric_limits<std::uint64_t>::max() - n < m) {
		throw std::overflow_error("Exponents overflow");
	}

	for (const auto &[exp_a, coef_a]: this->terms()){
		for (const auto &[exp_b, coef_b]: rhs.terms()){
			res.add_term(exp_a + exp_b, coef_a * coef_b);
		}
	}
	return res;
}

Polynomial Polynomial::pow(std::uint64_t exponent) const {
	if (exponent == 0) {
		Polynomial p;
		p.add_term(0, Rational(1));
		return p;
	}

	Polynomial cur = *this;
	Polynomial res = cur;

	for (std::uint64_t i(1); i < exponent; ++i) {
		res = res * cur;
	}
	return res;
}

bool Polynomial::is_zero() const {
	return _terms.empty();
}

const std::map<std::uint64_t, Rational> &Polynomial::terms() const {
	return _terms;
}
