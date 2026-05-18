#include "../../include/interpreter/Parser.hpp"
#include <vector>

Parser::Parser(std::vector<Token> tokens) :
	tokens(std::move(tokens)),
	current(0) {}

// let's start with only parsing assignments
// NOTE: how to start this shit?
stmt_ptr Parser::parse() {
	parse_assignment();
	return nullptr;
}

stmt_ptr Parser::parse_statement() {
	return nullptr;
}

// an assignment only consists of IDENT '=' expression
stmt_ptr Parser::parse_assignment() {
	if (peek().type == token_type::Ident && peek(1).type == token_type::Assign) {
		Token t = advance();
		return new AssignmentStmt(advance().lexeme,);
	}
	return nullptr;
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
	return nullptr;
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
	return tokens[current + offset];
}

Token Parser::advance() {
	return tokens[current++];
}

bool Parser::match(token_type t) {
	if (peek().type == t) {
		advance();
		return true;
	}
	return false;
}
