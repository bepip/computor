#pragma once

#include "../mathlib/Polynomial.hpp"
#include "AST.hpp"
#include "Context.hpp"
#include <optional>
#include <string>

class Simplifier {
  private:
	const Context &_context;
	std::string _parameter;

  public:
	Simplifier(const Context &context, std::string parameter) :
		_context(context),
		_parameter(parameter) {}

	expr_ptr simplify(const Expression *expr) const;

  private:
	expr_ptr simplify_node(const Expression *expr) const;
	expr_ptr simplify_number(const NumberExpr *expr) const;
	expr_ptr simplify_binary(const BinaryExpr *expr) const;
	expr_ptr simplify_unary(const UnaryExpr *expr) const;
	expr_ptr simplify_variable(const VariableExpr *expr) const;
	expr_ptr fold_constants(const NumberExpr *lhs, const NumberExpr *rhs,
							operation op) const;
	std::optional<Polynomial> to_polynomial(const Expression *expr) const;
	expr_ptr from_polynomial(const Polynomial &poly) const;
	expr_ptr build_var_tree(const std::uint64_t exponent) const;
	expr_ptr build_coef_tree(const Rational &coefficient) const;
	expr_ptr build_term_tree(const std::uint64_t exponent,
							 const Rational &coefficient) const;
};
