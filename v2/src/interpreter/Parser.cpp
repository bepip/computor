#include "../../include/interpreter/Parser.hpp"
#include <memory>
#include <vector>

Parser::Parser(std::vector<Token> tokens) :
	tokens(std::move(tokens)),
	pos(0) {}

// let's start with only parsing assignments
// NOTE: how to start this shit?
stmt_ptr Parser::parse() {
	return parse_assignment();
}

stmt_ptr Parser::parse_statement() {
	return nullptr;
}

// an assignment only consists of IDENT '=' expression
stmt_ptr Parser::parse_assignment() {
	const Token &name = consume(token_type::Ident, "Expected identifier");
	consume(token_type::Assign, "Expected '=");
	expr_ptr expr = parse_expression();
	return std::make_unique<AssignmentStmt>(name.lexeme, std::move(expr));
}

stmt_ptr Parser::parse_function_definition() {
	return nullptr;
}

stmt_ptr Parser::parse_expression_statement() {
	return nullptr;
}

stmt_ptr Parser::parse_query_statement() {
	return nullptr;
}

// expression:= term (('+' | '-') term)*
expr_ptr Parser::parse_expression() {
	auto left = parse_term();
	while (match(token_type::Plus) || match(token_type::Minus)) {
		char op = previous().lexeme[0];
		auto right = parse_term();
		
		left = std::make_unique<BinaryExpr>(std::move(left), op, std::move(right));
	}
	return left;
}

// term:= factor (('*' | '/') factor)*
expr_ptr Parser::parse_term() {
	return nullptr;
}

expr_ptr Parser::parse_unary() {
	return nullptr;
}

// NOTE: for now just focus on numbers
//  factor:= NUMBER | IDENT | '(' expression ')'
expr_ptr Parser::parse_factor() {
	return nullptr;
}

Token Parser::peek(size_t offset) const {
	return tokens[pos + offset];
}

Token Parser::advance() {
	return tokens[pos++];
}

bool Parser::match(token_type t) {
	if (peek().type == t) {
		advance();
		return true;
	}
	return false;
}
