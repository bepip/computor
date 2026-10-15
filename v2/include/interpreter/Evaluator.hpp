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
	Value evaluate_function_def(const FunctionDefStmt *stmt);
	[[nodiscard]]
	Value apply_binary(operation op, Value lhs, Value rhs);
	[[nodiscard]]
	Value apply_unary(operation op, Value operand);
	[[nodiscard]]
	Value evaluate_matrix(const MatrixExpr *expr);

	[[nodiscard]]
	Value compute_rational(operation op, Value lhs, Value rhs);
	[[nodiscard]]
	Value compute_matrix(operation op, Value lhs, Value rhs);
	[[nodiscard]]
	Value compute_complex(operation op, Value lhs, Value rhs);
	[[nodiscard]]
	Value compute_rational_complex(operation op, Value lhs, Value rhs);
	[[nodiscard]]
	Value compute_complex_rational(operation op, Value lhs, Value rhs);
	[[nodiscard]]
	Value compute_rational_matrix(operation op, Value lhs, Value rhs);
	[[nodiscard]]
	Value compute_matrix_rational(operation op, Value lhs, Value rhs);

  public:
	explicit Evaluator(Context &context) :
		context(context) {}

	[[nodiscard]]
	Value evaluate(const Statement *stmt);
};
