#include "../../include/interpreter/Evaluator.hpp"
#include "../../include/interpreter/error/InterpreterError.hpp"
#include <iostream>
#include <stdexcept>

Value Evaluator::evaluate(const Statement *stmt) {
	return evaluate_statement(stmt);
}

Value Evaluator::evaluate_statement(const Statement *stmt) {
	if (auto assign = dynamic_cast<const AssignmentStmt *>(stmt)) {
		std::cout << "Evaluator: Assignment: " << assign->name << "\n";
		auto value = evaluate_expression(assign->value.get());
		context.variables.insert_or_assign(assign->name, value);
		// throw std::logic_error("Evaluator: AssigbmentStmt: Not implemented yet");
		return value;
	} else if (auto function = dynamic_cast<const FunctionDefStmt *>(stmt)) {
		std::cout << "Evaluator: FunctionDef('" << function->name << "("
				  << function->parameter << ")" << "')\n";
		// TODO: idk how to handle functions yet
		// NOTE: save function name in context with reduced body etc
		auto value = evaluate_expression(function->body.get());
		throw std::logic_error("Evaluator: FunctionDefStmt: Not implemented yet");
		return value;
	} else if (auto expr_stmt = dynamic_cast<const ExpressionStmt *>(stmt)) {
		return evaluate_expression(expr_stmt->expr.get());
	} else if (auto eval = dynamic_cast<const EvalStmt *>(stmt)) {
		auto value = evaluate_expression(eval->expr.get());
		throw std::logic_error("Evaluator: EvalStmt: Not implemented yet");
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
		return Value{Rational(number->value)};
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
		char op = unary->op;
		Value operand = evaluate_expression(unary->operand.get());
		return apply_unary(op, operand);
	}
	throw InterpreterError("Evaluator", "Unsupported expression");
}

Value Evaluator::apply_binary(char op, Value lhs, Value rhs) {
	if (lhs.is<Rational>() && rhs.is<Rational>()) {
		return compute_rational(op, lhs, rhs);
	}
	throw InterpreterError("Evaluator", "Can't compute this");
}

Value Evaluator::apply_unary(char op, Value operand) {
	if (op == '+') {
		return operand;
	}
	if (operand.is<Rational>()) {
		const Rational &r = operand.get<Rational>();
		return Value{-Rational(r)};
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
