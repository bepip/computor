#pragma once

#include "../mathlib/Value.hpp"
#include "AST.hpp"
#include "Context.hpp"

class Evaluator {
  private:
	Context &context;

	[[nodiscard]]
	Value evaluate_expression(const Expression *expr);
	[[nodiscard]]
	Value evaluate_statement(const Statement *stmt);

	[[nodiscard]]
	Value apply_binary(char op, Value lhs, Value rhs);

	[[nodiscard]]
	Value compute_rational(char op, Value lhs, Value rhs);
	[[nodiscard]]
	Value compute_matrix(char op, Value lhs, Value rhs);
	[[nodiscard]]
	Value compute_complex(char op, Value lhs, Value rhs);


  public:
	explicit Evaluator(Context &context) :
		context(context) {}

	[[nodiscard]]
	Value evaluate(const Statement *stmt);
};
