#include "../../include/interpreter/Parser.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string_view>
#include <vector>

Parser::Parser(std::vector<Token> tokens) :
	tokens(std::move(tokens)),
	pos(0) {}

// let's start with only parsing assignments
// NOTE: how to start this shit?
//		 for now i only handle assignments, no idea how do differentiate
// between different types of inputs
[[nodiscard]] stmt_ptr Parser::parse() { return parse_statement(); }

[[nodiscard]] stmt_ptr Parser::parse_statement() {
	if (is_function_definition()) {
		return parse_function_definition();
	}
	if (is_assignment()) {
		return parse_assignment();
	}
	return parse_expression_statement();
}

// an assignment only consists of IDENT '=' expression
[[nodiscard]] stmt_ptr Parser::parse_assignment() {
	const Token &name = consume(token_type::Ident, "Expected identifier");
	consume(token_type::Assign, "Expected '='");
	expr_ptr expr = parse_expression();
	return std::make_unique<AssignmentStmt>(name.lexeme, std::move(expr));
}

// IDENT '(' IDENT ')' '=' expression
[[nodiscard]]
stmt_ptr Parser::parse_function_definition() {
	const Token &name = consume(token_type::Ident, "Expected identifier");
	consume(token_type::LParen, "Expected '(");
	const Token &parameter = consume(token_type::Ident, "Expected identifier");
	consume(token_type::RParen, "Expected ')'");
	consume(token_type::Assign, "Expected '='");
	auto expr = parse_expression();
	return std::make_unique<FunctionDefStmt>(name.lexeme, parameter.lexeme, std::move(expr));
}

// expression_statement:= expression
[[nodiscard]]
stmt_ptr Parser::parse_expression_statement() {
	auto expr = parse_expression();
	return std::make_unique<ExpressionStmt>(std::move(expr));
}

// NOTE: query_stmt:= expression '=' '?'
// TODO: handle function resolution where '=' and '?' don't follow each other
//		 move this logic inside parse_expression
[[nodiscard]] stmt_ptr Parser::parse_query_statement() {
	auto expr = parse_expression();
	consume(token_type::Assign, "Expected '=' before '?'");
	consume(token_type::Query, "Expected '?' after '='");

	return std::make_unique<QueryStmt>(std::move(expr));
}

// NOTE: current:
// expression:= term (('+' | '-') term)*
[[nodiscard]] expr_ptr Parser::parse_expression() {
	auto left = parse_term();
	while (match(token_type::Plus) || match(token_type::Minus)) {
		char op = previous().lexeme[0];
		auto right = parse_term();

		left =
			std::make_unique<BinaryExpr>(std::move(left), op, std::move(right));
	}
	return left;
}

// term:= factor (('*' | '/') factor)*
[[nodiscard]] expr_ptr Parser::parse_term() {
	auto left = parse_factor();
	for (;;) {
		if (match(token_type::Mul)) {
			auto right = parse_factor();
			left = std::make_unique<BinaryExpr>(std::move(left), '*', std::move(right));
		} else if (match(token_type::Div)) {
			auto right = parse_factor();
			left = std::make_unique<BinaryExpr>(std::move(left), '/', std::move(right));
		} else if (is_implicit_multiplication()) {
			auto right = parse_factor();
			left = std::make_unique<BinaryExpr>(std::move(left), '*', std::move(right));
		} else {
			break;
		}
	}
	return left;
}

[[deprecated("Not implemented")]] [[nodiscard]]
expr_ptr Parser::parse_unary() {
	return nullptr;
}

// NOTE: for now just focus on numbers
//  factor:= NUMBER | IDENT | '(' expression ')'
// TODO: handle function calls
// factor := NUMBER | IDENT ('(' expression ')')? | '(' expression ')'
[[nodiscard]] expr_ptr Parser::parse_factor() {
	if (match(token_type::Number)) {
		return std::make_unique<NumberExpr>(previous().value);
	}

	if (match(token_type::Ident)) {
		return std::make_unique<VariableExpr>(previous().lexeme);
	}

	if (match(token_type::LParen)) {
		auto expr = parse_expression();
		consume(token_type::RParen, "Expected ')'");
		return expr;
	}
	throw std::runtime_error("Expected expression");
}

//=============================================================================
// NOTE: HELPERS

[[nodiscard]] const Token &Parser::peek(size_t offset) const {
	return tokens[pos + offset];
}

[[nodiscard]] const Token &Parser::previous() const { return tokens[pos - 1]; }

[[nodiscard]] bool Parser::is_at_end() const {
	return peek().type == token_type::End;
}

[[nodiscard]] const Token &Parser::consume(token_type type, std::string_view message) {
	if (type != peek().type) {
		throw std::runtime_error(std::string(message));
	}
	return tokens[pos++];
}

bool Parser::match(token_type t) {
	if (peek().type != t) {
		return false;
	}
	++pos;
	return true;
}

[[nodiscard]] bool Parser::is_assignment() const {
	return peek().type == token_type::Ident &&
		   peek(1).type == token_type::Assign;
}

[[nodiscard]] bool Parser::is_function_definition() const {
	return peek().type == token_type::Ident &&
		   peek(1).type == token_type::LParen &&
		   peek(2).type == token_type::Ident &&
		   peek(3).type == token_type::RParen &&
		   peek(4).type == token_type::Assign;
}

// NOTE:we have an implicit multiplication when:
//		-> 2x
//		-> 2(
//		-> )2
//		-> )x
//		-> x(
//		-> )(
bool Parser::is_implicit_multiplication() const {
	token_type current = peek().type;
	if (pos == 0)
		return false;

	token_type prev = previous().type;
	bool left = prev == token_type::Number ||
				prev == token_type::Ident ||
				prev == token_type::RParen;

	bool right = current == token_type::Number ||
				 current == token_type::Ident ||
				 current == token_type::LParen;

	if (prev == token_type::Number && current == token_type::Number) {
		return false;
	}
	return left && right;
}

//=============================================================================
// NOTE: ASTPrinter could be in its own file

void ASTPrinter::print(const Statement *stmt) { print_statement(stmt, 0); }

void ASTPrinter::print_statement(const Statement *stmt, size_t level) {
	if (auto assign = dynamic_cast<const AssignmentStmt *>(stmt)) {
		indent(level);

		std::cout << "Assignment(" << assign->name << ")\n";
		print_expression(assign->value.get(), level + 1);
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
