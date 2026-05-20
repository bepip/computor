#include "../../include/interpreter/ASTPrinter.hpp"
#include <iostream>

void ASTPrinter::print(const Statement *stmt) { print_statement(stmt, 0); }

void ASTPrinter::print_statement(const Statement *stmt, size_t level) {
	if (auto assign = dynamic_cast<const AssignmentStmt *>(stmt)) {
		indent(level);

		std::cout << "Assignment(" << assign->name << ")\n";
		print_expression(assign->value.get(), level + 1);
		return;
	}
	if (auto function = dynamic_cast<const FunctionDefStmt *>(stmt)) {
		indent(level);

		std::cout << "FunctionDef('" << function->name
				  << "(" << function->parameter << ")" << "')\n";
		print_expression(function->body.get(), level + 1);
		return;
	}
	if (auto expr = dynamic_cast<const ExpressionStmt *>(stmt)) {
		indent(level);

		std::cout << "Expression:\n";
		print_expression(expr->expr.get(), level + 1);
		return;
	}
	if (auto eval = dynamic_cast<const EvalStmt *>(stmt)) {
		indent(level);

		std::cout << "Evaluation:\n";
		print_expression(eval->expr.get(), level + 1);
		return;
	}
	if (auto equation = dynamic_cast<const SolveStmt *>(stmt)) {
		indent(level);

		std::cout << "Solve:\n";
		indent(level + 1);
		std::cout << "Left:\n";
		print_expression(equation->left.get(), level + 2);

		indent(level + 1);
		std::cout << "Right:\n";
		print_expression(equation->right.get(), level + 2);
		return;
	}
	indent(level);
	std::cout << "Unknown statement\n";
}

void ASTPrinter::print_expression(const Expression *expr, size_t level) {
	if (auto number = dynamic_cast<const NumberExpr *>(expr)) {
		indent(level);
		std::cout << "NumberExpr(" << number->value << ")\n";
		return;
	}

	if (auto variable = dynamic_cast<const VariableExpr *>(expr)) {
		indent(level);
		std::cout << "VariableExpr(" << variable->name << ")\n";
		return;
	}

	if (auto binary = dynamic_cast<const BinaryExpr *>(expr)) {
		indent(level);
		switch (binary->op) {
			case '+': std::cout << "AddExpr\n"; break;
			case '-': std::cout << "SubExpr\n"; break;
			case '*': std::cout << "MulExpr\n"; break;
			case '/': std::cout << "DivExpr\n"; break;
			case '^': std::cout << "PowerExpr\n"; break;
		}
		print_expression(binary->left.get(), level + 1);
		print_expression(binary->right.get(), level + 1);
		return;
	}
	if (auto function = dynamic_cast<const FunctionCallExpr *>(expr)) {
		indent(level);
		std::cout << "FuncCall(" << function->name << ")\n";
		print_expression(function->argument.get(), level + 1);
		return;
	}
	if (auto unary = dynamic_cast<const UnaryExpr *>(expr)) {
		indent(level);
		std::cout << "UnaryExpr(" << unary->op << ")\n";
		print_expression(unary->operand.get(), level + 1);
		return;
	}
	indent(level);
	std::cout << "Unknown expression\n";
}

void ASTPrinter::indent(size_t level) {
	for (size_t i = 0; i < level; ++i) {
		std::cout << "  ";
	}
}
