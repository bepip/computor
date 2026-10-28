#include "../../include/mathlib/Polynomial.hpp"
#include <cstdint>
#include <limits>
#include <stdexcept>

void Polynomial::add_term(std::uint64_t exponent, const Rational &coefficient,
						  bool is_sub) {
	if (coefficient == Rational(0)) {
		return;
	}
	auto it = _terms.find(exponent);
	if (it == _terms.end()) {
		_terms.emplace(exponent, (is_sub ? -coefficient : coefficient));
		return;
	}
	const Rational res = (is_sub ? it->second - coefficient : it->second + coefficient);
	if (res == Rational(0)) {
		_terms.erase(it);
	} else {
		it->second = res;
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
		p.add_term(exp, coef, true);
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

	for (const auto &[exp_a, coef_a] : this->terms()) {
		for (const auto &[exp_b, coef_b] : rhs.terms()) {
			res.add_term(exp_a + exp_b, coef_a * coef_b);
		}
	}
	return res;
}

// NOTE:: return Q and R satisfying *this(dividend) = divisor * Q + R
//							 *this(dividend)/divisor = Q + R/divisor
std::pair<Polynomial, Polynomial> Polynomial::divmod(const Polynomial &divisor) const {
	Polynomial quotient;
	Polynomial remainder;
	Polynomial div;

	if (divisor.is_zero())
		throw std::domain_error("Dividing by zero.");
	if (this->is_zero()) {
		return {quotient, remainder};
	}
	if (this->degree() < divisor.degree()) {
		remainder = *this;
		return {quotient, remainder};
	}
	if (divisor.degree() == 0) { // divide by a constant
		const Rational constant = divisor.terms().begin()->second;
		for (const auto &[exp, coef] : this->terms()) {
			quotient.add_term(exp, coef / constant);
		}
		return {quotient, remainder};
	}
	remainder = *this;
	while (!remainder.is_zero() && remainder.degree() >= divisor.degree()) {
		const auto tmp = remainder.lead().lead_div(divisor.lead());
		quotient = quotient + tmp;
		remainder = remainder - tmp * divisor;
	}
	return {quotient, remainder};
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

std::uint64_t Polynomial::degree() const {
	if (this->is_zero()) {
		return 0;
	}
	return this->terms().rbegin()->first;
}

Polynomial Polynomial::lead() const {
	if (this->is_zero()) {
		return {};
	}
	Polynomial p;
	p.add_term(this->terms().rbegin()->first, this->terms().rbegin()->second);
	return p;
}

Polynomial Polynomial::lead_div(const Polynomial &divisor) const {
	const auto &lhs_terms = this->terms();
	const auto &rhs_terms = divisor.terms();
	if (lhs_terms.size() != 1 || rhs_terms.size() != 1) {
		throw std::runtime_error("Unexpected error");
	}
	const auto &lhs_degree = this->degree();
	const auto &rhs_degree = divisor.degree();
	if (lhs_degree < rhs_degree) {
		throw std::runtime_error("Unexpected error: divisor degree higher then dividend");
	}
	auto const degree = lhs_degree - rhs_degree;
	auto const coeff = lhs_terms.begin()->second / rhs_terms.begin()->second;
	Polynomial res;
	res.add_term(degree, coeff);
	return res;
}

const std::map<std::uint64_t, Rational> &Polynomial::terms() const {
	return _terms;
}
