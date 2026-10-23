#include "../../include/interpreter/Evaluator.hpp"
#include "../../include/interpreter/error/InterpreterError.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

Value Evaluator::evaluate(const Statement *stmt) {
	return evaluate_statement(stmt);
}

Value Evaluator::evaluate_statement(const Statement *stmt) {
	if (auto assign = dynamic_cast<const AssignmentStmt *>(stmt)) {
		auto value = evaluate_expression(assign->value.get());
		context.add_var(assign->name, value);
		// throw std::logic_error("Evaluator: AssigbmentStmt: Not implemented yet");
		return value;
	} else if (auto function = dynamic_cast<const FunctionDefStmt *>(stmt)) {
		std::cout << "Evaluator: FunctionDef('" << function->name << "("
				  << function->parameter << ")" << "')\n";
		// TODO: idk how to handle functions yet
		// NOTE: save function name in context with reduced body etc
		auto value = evaluate_function_def(function);
		// throw std::logic_error("Evaluator: FunctionDefStmt: Not implemented yet");
		return value;
	} else if (auto expr_stmt = dynamic_cast<const ExpressionStmt *>(stmt)) {
		return evaluate_expression(expr_stmt->expr.get());
	} else if (auto eval = dynamic_cast<const EvalStmt *>(stmt)) {
		auto value = evaluate_expression(eval->expr.get());
		//throw std::logic_error("Evaluator: EvalStmt: Not implemented yet");
		return value;
	} else if (auto equation = dynamic_cast<const SolveStmt *>(stmt)) {
		auto lhs = evaluate_expression(equation->left.get());
		auto rhs = evaluate_expression(equation->right.get());

		throw std::logic_error("Evaluator: SolveStmt: Not implemented yet");
		return {};
	}
	throw InterpreterError("Evaluator", "Unsupported statement");
}

Value Evaluator::evaluate_expression(const Expression *expr) {
	if (auto number = dynamic_cast<const NumberExpr *>(expr)) {
		if (number->is_literal())
			return Value{Rational(std::get<std::string>(number->value))};
		if (number->is_value())
			return std::get<Value>(number->value);
	} else if (dynamic_cast<const ImagExpr *>(expr)) {
		return Value{Complex(0, 1)};
	} else if (auto variable = dynamic_cast<const VariableExpr *>(expr)) {
		if (auto opt = context.get_var(variable->name)) {
			return opt.value();
		}
		// TODO: create a runtime/context error class to print math related errors
		throw InterpreterError("math todo", "Variable not found");
	} else if (auto binary = dynamic_cast<const BinaryExpr *>(expr)) {
		Value left = evaluate_expression(binary->left.get());
		Value right = evaluate_expression(binary->right.get());
		return apply_binary(binary->op, left, right);
	} else if (auto function = dynamic_cast<const FunctionCallExpr *>(expr)) {
		(void)function;
		throw InterpreterError("Evaluator", "FunctionCallExpr not implemented yet");
	} else if (auto unary = dynamic_cast<const UnaryExpr *>(expr)) {
		operation op = unary->op;
		Value operand = evaluate_expression(unary->operand.get());
		return apply_unary(op, operand);
	} else if (auto matrix = dynamic_cast<const MatrixExpr *>(expr)) {
		return evaluate_matrix(matrix);
	}
	throw InterpreterError("Evaluator", "Unsupported expression");
}

Value Evaluator::evaluate_function_def(const FunctionDefStmt *stmt) {
	Function func(stmt->parameter, stmt->body->clone());
	context.add_func(stmt->name, std::move(func));
	return {};
}

Value Evaluator::apply_binary(operation op, Value lhs, Value rhs) {
	if (lhs.is<Rational>() && rhs.is<Rational>()) {
		return compute_rational(op, lhs, rhs);
	}
	if (lhs.is<Complex>() && rhs.is<Rational>()) {
		return compute_complex_rational(op, lhs, rhs);
	}
	if (lhs.is<Rational>() && rhs.is<Complex>()) {
		return compute_rational_complex(op, lhs, rhs);
	}
	if (lhs.is<Complex>() && rhs.is<Complex>()) {
		return compute_complex(op, lhs, rhs);
	}
	if (lhs.is<Matrix>() && rhs.is<Matrix>()) {
		return compute_matrix(op, lhs, rhs);
	}
	if (lhs.is<Matrix>() && rhs.is<Rational>()) {
		return compute_matrix_rational(op, lhs, rhs);
	}
	if (lhs.is<Rational>() && rhs.is<Matrix>()) {
		return compute_rational_matrix(op, lhs, rhs);
	}
	throw InterpreterError("Evaluator", "Can't compute this");
}

Value Evaluator::apply_unary(operation op, Value operand) {
	if (op == operation::Add) {
		return operand;
	}
	if (operand.is<Rational>()) {
		const Rational &r = operand.get<Rational>();
		return Value{Rational(-r)};
	}
	if (operand.is<Complex>()) {
		const Complex &c = operand.get<Complex>();
		return Value{-Complex(c)};
	}
	throw InterpreterError("Evaluator", "Can't apply unary to this expression");
}

Value Evaluator::evaluate_matrix(const MatrixExpr *expr) {
	const std::vector<std::vector<expr_ptr>> &rows = expr->rows;

	std::vector<Rational> matrix;
	const size_t size_row = rows.size();
	const size_t size_col = rows[0].size();
	matrix.reserve(size_col * size_row);

	for (const auto &row : rows) {
		for (const auto &val : row) {
			const auto value = evaluate_expression(val.get());
			if (!value.is<Rational>()) {
				throw std::invalid_argument("Element of matrix is not a Rational");
			}
			matrix.push_back(value.get<Rational>());
		}
	}
	return Value{Matrix(size_row, size_col, matrix)};
}

Value Evaluator::compute_rational(operation op, Value lhs, Value rhs) {
	const Rational &left = lhs.get<Rational>();
	const Rational &right = rhs.get<Rational>();
	switch (op) {
		case operation::Add:
			return Value{left + right};
		case operation::Sub:
			return Value{left - right};
		case operation::Mul:
			return Value{left * right};
		case operation::Div:
			return Value{left / right};
		case operation::Mod:
			return Value{left % right};
		case operation::Pow:
			return Value{left ^ right};
		default:
			throw std::runtime_error("Rational: Unknown operator");
	}
}

Value Evaluator::compute_matrix(operation op, Value lhs, Value rhs) {
	const Matrix &left = lhs.get<Matrix>();
	const Matrix &right = rhs.get<Matrix>();
	switch (op) {
		case operation::Add:
			return Value{left + right};
		case operation::Sub:
			return Value{left - right};
		case operation::Mul:
			return Value{left * right};
		case operation::MatrixMul:
			return Value{left.matrix_multiplication(right)};
		default:
			throw std::runtime_error("Matrix: Unknown operator");
	}
	throw std::runtime_error("Matrix: Unknown operator");
};

Value Evaluator::compute_complex(operation op, Value lhs, Value rhs) {
	const Complex &left = lhs.get<Complex>();
	const Complex &right = rhs.get<Complex>();
	Complex res;
	switch (op) {
		case operation::Add:
			res = left + right;
			break;
		case operation::Sub:
			res = left - right;
			break;
		case operation::Mul:
			res = left * right;
			break;
		case operation::Div:
			res = left / right;
			break;
		default:
			std::string err =
				"Can't use '" + operation_to_string(op) + "' on complex numbers";
			throw std::runtime_error(err);
	}
	if (res.imag() == 0) {
		return Value{Rational(res.real())};
	}
	return Value{res};
}

Value Evaluator::compute_rational_complex(operation op, Value lhs, Value rhs) {
	const Value left = Value{Complex(lhs.get<Rational>())};
	return compute_complex(op, left, rhs);
}

Value Evaluator::compute_complex_rational(operation op, Value lhs, Value rhs) {
	const Value right = Value{Complex(rhs.get<Rational>())};
	return compute_complex(op, lhs, right);
}

Value Evaluator::compute_rational_matrix(operation op, Value lhs, Value rhs) {
	if (op != operation::Mul) {
		std::string err =
			"Can't use  '" + operation_to_string(op) + "' between a scalar and a matrix";
		throw std::logic_error(err);
	}
	const Rational scalar = lhs.get<Rational>();
	const Matrix m = rhs.get<Matrix>();
	return Value{m * scalar};
}

Value Evaluator::compute_matrix_rational(operation op, Value lhs, Value rhs) {
	return compute_rational_matrix(op, rhs, lhs);
}
