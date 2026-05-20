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

		std::cout << "Function('" << function->name
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
		std::cout << "BinaryExpr(" << binary->op << ")\n";
		print_expression(binary->left.get(), level + 1);
		print_expression(binary->right.get(), level + 1);
		return;
	}

	std::cout << "Unknown expression\n";
}

void ASTPrinter::indent(size_t level) {
	for (size_t i = 0; i < level; ++i) {
		std::cout << " ";
	}
}
