#pragma once

#include "../mathlib/Value.hpp"
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

enum class operation {
	Add,	   // +
	Sub,	   // -
	Mod,	   // %
	Mul,	   // *
	Div,	   // /
	Pow,	   // ^
	MatrixMul, // **
};

[[nodiscard]]
std::optional<operation> operation_from_char(char c);
std::string operation_to_string(operation op);

class Expression;
class Statement;

class ASTNode {
  public:
	virtual ~ASTNode() = default;
};

class Expression : public ASTNode {
  public:
	virtual ~Expression() = default;
	virtual std::unique_ptr<Expression> clone() const = 0;
};

class Statement : public ASTNode {
  public:
	virtual ~Statement() = default;
};

using expr_ptr = std::unique_ptr<Expression>;
using stmt_ptr = std::unique_ptr<Statement>;

class NumberExpr : public Expression {
  public:
	std::variant<std::string, Value> value;

	explicit NumberExpr(const std::string &value) :
		value(value) {}

	explicit NumberExpr(Value value) :
		value(std::move(value)) {}

	[[nodiscard]]
	Rational as_rational() const;

	bool is_literal() const;

	bool is_value() const;

	expr_ptr clone() const override { return std::make_unique<NumberExpr>(*this); };
};

class ImagExpr : public Expression {
	expr_ptr clone() const override { return std::make_unique<ImagExpr>(); };
};

class MatrixExpr : public Expression {
  public:
	std::vector<std::vector<expr_ptr>> rows;

	MatrixExpr(std::vector<std::vector<expr_ptr>> rows) :
		rows(std::move(rows)) {}

	expr_ptr clone() const override {
		std::vector<std::vector<expr_ptr>> cloned;
		cloned.reserve(rows.size());
		for (const auto &row : rows) {
			std::vector<expr_ptr> new_row;
			new_row.reserve(row.size());
			for (const auto &exp : row) {
				new_row.push_back(exp->clone());
			}
			cloned.push_back(std::move(new_row));
		}
		return std::make_unique<MatrixExpr>(std::move(cloned));
	};
};

class VariableExpr : public Expression {
  public:
	std::string name;

	VariableExpr(std::string_view name) :
		name(name) {}

	expr_ptr clone() const override { return std::make_unique<VariableExpr>(name); };
};

class UnaryExpr : public Expression {
  public:
	operation op;
	expr_ptr operand;

	UnaryExpr(operation op, expr_ptr operand) :
		op(std::move(op)),
		operand(std::move(operand)) {}

	expr_ptr clone() const override {
		return std::make_unique<UnaryExpr>(op, operand->clone());
	};
};

class BinaryExpr : public Expression {
  public:
	expr_ptr left;
	operation op;
	expr_ptr right;

	BinaryExpr(expr_ptr left, operation op, expr_ptr right) :
		left(std::move(left)),
		op(std::move(op)),
		right(std::move(right)) {}

	expr_ptr clone() const override {
		return std::make_unique<BinaryExpr>(left->clone(), op, right->clone());
	};
};

class FunctionCallExpr : public Expression {
  public:
	std::string name;
	expr_ptr argument;

	FunctionCallExpr(std::string_view name, expr_ptr argument) :
		name(name),
		argument(std::move(argument)) {}

	expr_ptr clone() const override {
		return std::make_unique<FunctionCallExpr>(name, argument->clone());
	};
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

class EvalStmt : public Statement {
  public:
	expr_ptr expr;

	EvalStmt(expr_ptr expr) :
		expr(std::move(expr)) {}
};

class SolveStmt : public Statement {
  public:
	expr_ptr left;
	expr_ptr right;

	SolveStmt(expr_ptr left, expr_ptr right) :
		left(std::move(left)),
		right(std::move(right)) {}
};
