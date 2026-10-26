#include "../../include/mathlib/Polynomial.hpp"

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

bool Polynomial::is_zero() const {
	return _terms.empty();
}

const std::map<std::uint64_t, Rational> &Polynomial::terms() const {
	return _terms;
}
