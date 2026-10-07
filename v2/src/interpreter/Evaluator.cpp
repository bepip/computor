#include "../../include/interpreter/Evaluator.hpp"
#include "../../include/interpreter/error/InterpreterError.hpp"
#include <stdexcept>

Value Evaluator::evaluate(const Statement *stmt) {
	return evaluate_statement(stmt);
}

Value Evaluator::evaluate_expression(const Expression *expr) {
	if (auto number = dynamic_cast<const NumberExpr *>(expr)) {
		return Value{Rational(number->value)};
	}
	if (auto binary = dynamic_cast<const BinaryExpr *>(expr)) {
		Value left = evaluate_expression(binary->left.get());
		Value right = evaluate_expression(binary->right.get());
		return apply_binary(binary->op, left, right);
	}
	throw InterpreterError("Evaluator", "Unsupported expression");
}

Value Evaluator::evaluate_statement(const Statement *stmt) {
	if (auto expr_stmt = dynamic_cast<const ExpressionStmt *>(stmt)) {
		return evaluate_expression(expr_stmt->expr.get());
	}
	throw InterpreterError("Evaluator", "Unsupported statement");
}

Value Evaluator::apply_binary(char op, Value lhs, Value rhs) {
	if (lhs.is<Rational>() && rhs.is<Rational>()) {
		return compute_rational(op, lhs, rhs);
	}
	throw InterpreterError("Evaluator", "Can't compute this");
}

Value Evaluator::compute_rational(char op, Value lhs, Value rhs) {
	const Rational &left = lhs.get<Rational>();
	const Rational &right = rhs.get<Rational>();
	switch (op) {
		case '+':
			return Value{left + right};
		case '-':
			return Value{left - right};
		case '*':
			return Value{left * right};
		case '/':
			return Value{left / right};
		case '%':
			return Value{left % right};
	}
	throw std::runtime_error("Rational: Unknown operator");
}

Value Evaluator::compute_matrix(char op, Value lhs, Value rhs) {
	const Matrix &left = lhs.get<Matrix>();
	const Matrix &right = rhs.get<Matrix>();
	switch (op) {
		case '+':
			return Value{left + right};
		case '-':
			return Value{left - right};
		case '*':
			return Value{left * right};
	}
	throw std::runtime_error("Matrix: Unknown operator");
};

Value Evaluator::compute_complex(char op, Value lhs, Value rhs) {
	const Complex &left = lhs.get<Complex>();
	const Complex &right = rhs.get<Complex>();
	switch (op) {
		case '+':
			return Value{left + right};
		case '-':
			return Value{left - right};
		case '*':
			return Value{left * right};
		case '/':
			return Value{left / right};
	}
	throw std::runtime_error("Complex: Unknown operator");
}
