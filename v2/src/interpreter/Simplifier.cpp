#include "../../include/interpreter/Simplifier.hpp"
#include <memory>
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
