#pragma once

#include <memory>
#include <string>
#include <string_view>

class ASTNode {
  public:
	virtual ~ASTNode() = default;
};

class Expression : public ASTNode {
  public:
	virtual ~Expression() = default;
};

class Statement : public ASTNode {
  public:
	virtual ~Statement() = default;
};

using expr_ptr = std::unique_ptr<Expression>;
using stmt_ptr = std::unique_ptr<Statement>;

class NumberExpr : public Expression {
  public:
	double value;

	NumberExpr(double value) :
		value(value) {}
};

class VariableExpr : public Expression {
  public:
	std::string name;

	VariableExpr(std::string_view name) :
		name(name) {}
};

class UnaryExpr : public Expression {
  public:
	char op;
	expr_ptr operand;

	UnaryExpr(char op, expr_ptr operand) :
		op(op),
		operand(std::move(operand)) {}
};

class BinaryExpr : public Expression {
  public:
	expr_ptr left;
	char op;
	expr_ptr right;

	BinaryExpr(expr_ptr left, char op, expr_ptr right) :
		left(std::move(left)),
		op(op),
		right(std::move(right)) {}
};

class FunctionCallExpr : public Expression {
  public:
	std::string name;
	expr_ptr argument;

	FunctionCallExpr(std::string_view name, expr_ptr argument) :
		name(name),
		argument(std::move(argument)) {}
};

class AssignmentStmt : public Statement {
  public:
	std::string name;
	expr_ptr value;

	AssignmentStmt(std::string_view name, expr_ptr value) :
		name(name),
		value(std::move(value)) {}
};

class FunctionDefStmt : public Statement {
  public:
	std::string name;
	std::string parameter;
	expr_ptr body;

	FunctionDefStmt(std::string_view name, std::string_view parameter, expr_ptr body) :
		name(name),
		parameter(parameter),
		body(std::move(body)) {}
};

class ExpressionStmt : public Statement {
  public:
	expr_ptr expr;

	ExpressionStmt(expr_ptr expr) :
		expr(std::move(expr)) {}
};

class QueryStmt : public Statement {
  public:
	expr_ptr expr;

	QueryStmt(expr_ptr expr) :
		expr(std::move(expr)) {}
};
