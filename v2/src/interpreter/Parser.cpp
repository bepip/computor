#include "../../include/interpreter/Parser.hpp"
#include <memory>
#include <stdexcept>
#include <string_view>
#include <vector>

Parser::Parser(std::vector<Token> tokens) :
	tokens(std::move(tokens)),
	pos(0) {}

[[nodiscard]] stmt_ptr Parser::parse() {
	auto stmt = parse_statement();
	if (is_at_end() == false) {
		throw std::runtime_error("Unexpected token found: " + peek().lexeme);
	}
	return stmt;
}

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

// TODO: for later: handle function resolution where '=' and '?' don't follow each other
//		 ex: f(x) = 25x + 3 ?

// expression_statement:= expression ('=' '?')?
[[nodiscard]]
stmt_ptr Parser::parse_expression_statement() {
	auto expr = parse_expression();
	if (peek().type == token_type::Assign && peek(1).type == token_type::Query) {
		consume(token_type::Assign, "Expected '=' before '?'");
		consume(token_type::Query, "Expected '?' after '='");
		return std::make_unique<QueryStmt>(std::move(expr));
	}
	return std::make_unique<ExpressionStmt>(std::move(expr));
}

// query_stmt:= expression '=' '?'
[[nodiscard]] [[deprecated("this is handled in parse_expression_statement")]]
stmt_ptr Parser::parse_query_statement() {
	auto expr = parse_expression();
	consume(token_type::Assign, "Expected '=' before '?'");
	consume(token_type::Query, "Expected '?' after '='");

	return std::make_unique<QueryStmt>(std::move(expr));
}

// expression:= term (('+' | '-') term)*
[[nodiscard]] expr_ptr Parser::parse_expression() {
	auto left = parse_term();
	while (match(token_type::Plus) || match(token_type::Minus)) {
		char op = previous().lexeme[0];
		auto right = parse_term();

		left = std::make_unique<BinaryExpr>(std::move(left), op, std::move(right));
	}
	return left;
}

// term:= unary (('*' | '/' | implicit_mul) unary)*
[[nodiscard]] expr_ptr Parser::parse_term() {
	auto left = parse_unary();
	for (;;) {
		if (match(token_type::Mul)) {
			auto right = parse_unary();
			left = std::make_unique<BinaryExpr>(std::move(left), '*', std::move(right));
		} else if (match(token_type::Div)) {
			auto right = parse_unary();
			left = std::make_unique<BinaryExpr>(std::move(left), '/', std::move(right));
		} else if (is_implicit_multiplication()) {
			auto right = parse_unary();
			left = std::make_unique<BinaryExpr>(std::move(left), '*', std::move(right));
		} else {
			break;
		}
	}
	return left;
}

// unary:= '-' power | power
expr_ptr Parser::parse_unary() {
	if (match(token_type::Minus)) {
		auto operand = parse_power();
		return std::make_unique<UnaryExpr>('-', std::move(operand));
	}
	return parse_power();
}

// power :=	factor ('^' power)?
[[nodiscard]] expr_ptr Parser::parse_power() {
	auto left = parse_factor();
	if (match(token_type::Power)) {
		auto right = parse_power();
		left = std::make_unique<BinaryExpr>(std::move(left), '^', std::move(right));
	}
	return left;
}

//  factor := NUMBER | IDENT | function_call | '(' expression ')'
[[nodiscard]] expr_ptr Parser::parse_factor() {
	if (match(token_type::Number)) {
		return std::make_unique<NumberExpr>(previous().value);
	}

	if (match(token_type::Ident)) {
		std::string_view name = previous().lexeme;
		if (peek().type == token_type::LParen) {
			return parse_function_call(name);
		}
		return std::make_unique<VariableExpr>(name);
	}

	if (match(token_type::LParen)) {
		auto expr = parse_expression();
		consume(token_type::RParen, "Expected ')'");
		return expr;
	}
	throw std::runtime_error("Expected expression");
}

// function_call := IDENT '(' expression ')'
[[nodiscard]] expr_ptr Parser::parse_function_call(std::string_view name) {
	consume(token_type::LParen, "Expected '('");
	auto arg = parse_expression();
	consume(token_type::RParen, "Expected ')'");
	return std::make_unique<FunctionCallExpr>(name, std::move(arg));
}

//=============================================================================
// NOTE: HELPERS

[[nodiscard]] const Token &Parser::peek(size_t offset) const {
	size_t index = pos + offset;
	if (index >= tokens.size()) {
		return tokens.back();
	}
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
//		-> )(
//	INFO:  x( => this will be a function call
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

	if (prev == token_type::Ident && current == token_type::LParen) {
		return false;
	}
	if (prev == token_type::Number && current == token_type::Number) {
		return false;
	}
	return left && right;
}
