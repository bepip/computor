#include "../../include/interpreter/Simplifier.hpp"
#include <cstdint>
#include <limits>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>

expr_ptr Simplifier::simplify(const Expression *expr) const {
	if (const auto &number = dynamic_cast<const NumberExpr *>(expr)) {
		return simplify_number(number);
	} else if (const auto &var = dynamic_cast<const VariableExpr *>(expr)) {
		return simplify_variable(var);
	} else if (const auto &unary = dynamic_cast<const UnaryExpr *>(expr)) {
		return simplify_unary(unary);
	} else if (const auto &binary = dynamic_cast<const BinaryExpr *>(expr)) {
		return simplify_binary(binary);
	}
	throw std::runtime_error("Invalid input");
}

expr_ptr Simplifier::simplify_number(const NumberExpr *expr) const {
	return expr->clone();
}

expr_ptr Simplifier::simplify_binary(const BinaryExpr *expr) const {
	auto lhs = simplify(expr->left.get());
	auto rhs = simplify(expr->right.get());

	auto left_num = dynamic_cast<const NumberExpr *>(lhs.get());
	auto right_num = dynamic_cast<const NumberExpr *>(rhs.get());

	if (right_num && right_num->as_rational() == Rational(0)) {
		if (expr->op == operation::Div)
			throw std::runtime_error("Division by zero");

		if (expr->op == operation::Mod)
			throw std::runtime_error("Modulo by zero");
	}

	if (left_num && right_num) {
		const Rational &a = left_num->as_rational();
		const Rational &b = right_num->as_rational();

		Rational result;

		switch (expr->op) {
			case operation::Add:
				result = a + b;
				break;
			case operation::Sub:
				result = a - b;
				break;
			case operation::Mul:
				result = a * b;
				break;
			case operation::Div:
				result = a / b;
				break;
			case operation::Mod:
				result = a % b;
				break;
			case operation::Pow:
				result = a ^ b;
				break;
			default:
				throw std::runtime_error("Unsupported binary operation");
		}
		return std::make_unique<NumberExpr>(Value{result});
	}
	if (left_num) {
		const Rational &a = left_num->as_rational();
		switch (expr->op) {
			case operation::Add:
				if (a == Rational(0)) {
					return rhs;
				}
				break;
			case operation::Sub:
				if (a == Rational(0)) {
					auto unary =
						std::make_unique<UnaryExpr>(operation::Sub, std::move(rhs));
					return simplify(unary.get());
				}
				break;
			case operation::Mul:
				if (a == Rational(1)) {
					return rhs;
				}
				if (a == Rational(0)) {
					return std::make_unique<NumberExpr>(Value{Rational{0}});
				}

			default:
				break;
		}
	}
	if (right_num) {
		const Rational &b = right_num->as_rational();
		switch (expr->op) {
			case operation::Add:
			case operation::Sub:
				if (b == Rational(0)) {
					return lhs;
				}
				break;
			case operation::Mul:
				if (b == Rational(1)) {
					return lhs;
				}
				if (b == Rational(0)) {
					return std::make_unique<NumberExpr>(Value{Rational{0}});
				}
				break;
			case operation::Div:
				if (b == Rational(1)) {
					return lhs;
				}
				break;
			case operation::Pow:

				if (b == Rational(1))
					return lhs;
				if (b == Rational(0))
					return std::make_unique<NumberExpr>(Value{Rational{1}});
				break;
			default:
				break;
		}
	}
	return std::make_unique<BinaryExpr>(std::move(lhs), expr->op, std::move(rhs));
}

expr_ptr Simplifier::simplify_unary(const UnaryExpr *expr) const {
	auto operand = simplify(expr->operand.get());

	if (auto number = dynamic_cast<const NumberExpr *>(operand.get())) {
		if (expr->op == operation::Sub) {
			return std::make_unique<NumberExpr>(Value{-number->as_rational()});
		}
	}

	if (auto unary = dynamic_cast<const UnaryExpr *>(operand.get())) {
		if (expr->op == operation::Sub && unary->op == operation::Sub) {
			return unary->operand->clone();
		}
	}
	return std::make_unique<UnaryExpr>(expr->op, std::move(operand));
}

expr_ptr Simplifier::simplify_variable(const VariableExpr *expr) const {
	if (expr->name == _parameter) {
		return expr->clone();
	}
	const auto &opt = _context.get_var(expr->name);
	if (!opt.has_value()) {
		const std::string err_msg = "expriable " + expr->name + " not found.";
		throw std::invalid_argument(err_msg);
	}
	const auto &value = std::move(*opt);
	if (!value.is<Rational>()) {
		throw std::invalid_argument("Functions only take Rationals");
	}
	return std::make_unique<NumberExpr>(value);
}

std::optional<Polynomial> Simplifier::to_polynomial(const Expression *expr) const {
	Polynomial p;
	if (const auto nb = dynamic_cast<const NumberExpr *>(expr)) {
		p.add_term(0, nb->as_rational());
		return p;
	}
	if (const auto var = dynamic_cast<const VariableExpr *>(expr)) {
		if (var->name != _parameter) {
			return std::nullopt;
		}
		p.add_term(1, Rational(1));
		return p;
	}
	if (const auto bin = dynamic_cast<const BinaryExpr *>(expr)) {
		switch (bin->op) {
			case operation::Add:
				{
					const auto lhs = to_polynomial(bin->left.get());
					const auto rhs = to_polynomial(bin->right.get());
					if (!lhs.has_value() || !rhs.has_value()) {
						return std::nullopt;
					}
					return lhs.value() + rhs.value();
				}
			case operation::Sub:
				{
					const auto lhs = to_polynomial(bin->left.get());
					const auto rhs = to_polynomial(bin->right.get());
					if (!lhs.has_value() || !rhs.has_value()) {
						return std::nullopt;
					}
					return lhs.value() - rhs.value();
				}
			case operation::Mul:
				{
					const auto lhs = to_polynomial(bin->left.get());
					const auto rhs = to_polynomial(bin->right.get());
					if (!lhs.has_value() || !rhs.has_value()) {
						return std::nullopt;
					}
					return lhs.value() * rhs.value();
				}
			case operation::Pow:
				{
					if (const auto nb =
							dynamic_cast<const NumberExpr *>(bin->right.get())) {
						Rational exp = nb->as_rational();
						if (!exp.is_integer() || !exp.is_nonnegative()) {
							return std::nullopt;
						}

						const auto base = to_polynomial(bin->left.get());
						if (base.has_value()) {
							return base->pow(static_cast<std::uint64_t>(exp.numerator()));
						}
					}
					return std::nullopt;
				}
			default:
				return std::nullopt;
		}
	}
	if (const auto unary = dynamic_cast<const UnaryExpr *>(expr)) {
		switch (unary->op) {
			case operation::Add:
				{
					const auto rhs = to_polynomial(unary->operand.get());
					if (!rhs.has_value()) {
						return std::nullopt;
					}
					return rhs.value();
				}
			case operation::Sub:
				{
					const auto rhs = to_polynomial(unary->operand.get());
					if (!rhs.has_value()) {
						return std::nullopt;
					}
					return p - rhs.value();
				}
			default:
				return std::nullopt;
		}
	}
	return std::nullopt;
}

expr_ptr Simplifier::from_polynomial(const Polynomial &poly) const {
	if (poly.is_zero()) {
		return std::make_unique<NumberExpr>(Value{Rational(0)});
	}
	auto it = poly.terms().rbegin();
	expr_ptr ast = build_term_tree(it->first, it->second);
	while (++it != poly.terms().rend()) {
		ast = std::make_unique<BinaryExpr>(std::move(ast), operation::Add,
										   build_term_tree(it->first, it->second));
	}
	return ast;
}

expr_ptr Simplifier::build_var_tree(const std::uint64_t exponent) const {
	if (exponent == 0) {
		return nullptr;
	}

	if (exponent > std::numeric_limits<std::int64_t>::max()) {
		throw std::overflow_error("Exponent overflow");
	}

	auto var = std::make_unique<VariableExpr>(_parameter);

	if (exponent == 1) {
		return var;
	}

	auto exp = std::make_unique<NumberExpr>(
		Value{Rational(static_cast<std::int64_t>(exponent))});
	return std::make_unique<BinaryExpr>(std::move(var), operation::Pow, std::move(exp));
}

expr_ptr Simplifier::build_coef_tree(const Rational &coefficient) const {
	if (coefficient == Rational(0)) {
		return nullptr;
	}
	return std::make_unique<NumberExpr>(Value{coefficient});
}

expr_ptr Simplifier::build_term_tree(const std::uint64_t exponent,
									 const Rational &coefficient) const {
	auto exp = build_var_tree(exponent);
	if (coefficient == Rational(1) && exp != nullptr) {
		return exp;
	}
	if (coefficient == Rational(-1) && exp != nullptr) {
		return std::make_unique<UnaryExpr>(operation::Sub, std::move(exp));
	}
	auto coef = build_coef_tree(coefficient);
	if (coef == nullptr) {
		// should never happen since a null coef is removed from the map
		throw std::runtime_error("Unexpected error: null coefficient");
	}
	if (exp == nullptr) {
		return coef;
	}
	return std::make_unique<BinaryExpr>(std::move(coef), operation::Mul, std::move(exp));
}
