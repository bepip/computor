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
	}
	throw std::runtime_error("Invalid input");
}

expr_ptr Simplifier::simplify_number(const NumberExpr *expr) const {
	return expr->clone();
}

expr_ptr Simplifier::simplify_binary(const BinaryExpr *expr) const {}

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
