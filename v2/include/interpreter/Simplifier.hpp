#pragma once
#include "AST.hpp"
#include "Context.hpp"
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
	expr_ptr simplify_number(const NumberExpr *expr) const;
	expr_ptr simplify_binary(const BinaryExpr *expr) const;
	expr_ptr simplify_unary(const UnaryExpr *expr) const;
	expr_ptr simplify_variable(const VariableExpr *expr) const;
};
