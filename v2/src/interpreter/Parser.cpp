#include "../../include/interpreter/Parser.hpp"
#include <vector>

Parser::Parser(std::vector<Token> tokens) :
	tokens(std::move(tokens)),
	current(0) {}

stmt_ptr Parser::parse() {
	Token first = peek();
	Token second = peek(1);
	Token third = peek(2);
	Token fourth = peek(3);
	Token fifth = peek(4);

	if (first.type == token_type::Ident) {
		if (second.type == token_type::Assign) {
			return parse_assignment();
		}
		if (second.type == token_type::LParen) {
			if (third.type == token_type::Ident) {
				return parse_function_definition();
			} else if (third.type == token_type::Number) {
				return 
			}
		}
	} else {
		return parse_expression_statement();
	}
	return nullptr;
}

stmt_ptr Parser::parse_statement() {
	return nullptr;
}

stmt_ptr Parser::parse_assignment() {
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

expr_ptr Parser::parse_expression() {
	return nullptr;
}

expr_ptr Parser::parse_term() {
	return nullptr;
}

expr_ptr Parser::parse_unary() {
	return nullptr;
}

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
