#include "../../include/interpreter/Lexer.hpp"
#include <cctype>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

Lexer::Lexer(std::string_view input) {
	src = input;
	pos = 0;
}

std::vector<Token> Lexer::tokenize() {
	std::vector<Token> tokens;

	Token t;
	do {
		t = nextToken();
		tokens.push_back(t);
	} while (t.type != token_type::End);
	return tokens;
}

Token Lexer::nextToken() {
	skipWhiteSpace();

	if (pos >= src.size())
		return {token_type::End, "", 0};
	char curr = currentChar();

	if (std::isdigit(curr))
		return number();

	switch (curr) {
		case '+':
			advance();
			return {token_type::Plus, "+", 0};
		case '-':
			advance();
			return {token_type::Minus, "-", 0};
		case '*':
			advance();
			return {token_type::Mul, "*", 0};
		case '/':
			advance();
			return {token_type::Div, "/", 0};
		case '(':
			advance();
			return {token_type::LParen, "(", 0};
		case ')':
			advance();
			return {token_type::RParen, ")", 0};
	}
	advance();
	return {token_type::Invalid, std::string(1, curr), 0};
}

void Lexer::advance() {
	++pos;
}

Token Lexer::number() {
	size_t start = pos;

	while (pos < src.size() && (isdigit(src[pos]) || src[pos] == '.')) {
		pos++;
	}
	std::string numStr = src.substr(start, pos - start);
	return {
		token_type::Number,
		numStr,
		std::stod(numStr),
	};
}

void Lexer::skipWhiteSpace() {
	while (pos < src.size() && isspace(src[pos])) {
		pos++;
	}
}

char Lexer::currentChar() const {
	return src[pos];
}

std::string Token::to_string() const {
	switch (type) {
		case token_type::Plus:
			return "PLUS_SIGN('" + lexeme + "')";
		case token_type::Minus:
			return "MINUS_SIGN('" + lexeme + "')";
		case token_type::Div:
			return "DIV_SIGN('" + lexeme + "')";
		case token_type::Mul:
			return "MUL_SIGN('" + lexeme + "')";
		case token_type::LParen:
			return "LPAREN('" + lexeme + "')";
		case token_type::RParen:
			return "RPAREN('" + lexeme + "')";
		case token_type::Number:
			return "NUMBER('" + lexeme + "')";
		case token_type::End:
			return "EOF";
		case token_type::Invalid:
			return "INVALID_TOKEN('" + lexeme + "')";
	}
	return "INVALID_TOKEN('" + lexeme + "')";
}

bool Token::operator==(const Token &t) const {
	return type == t.type && lexeme == t.lexeme && value == t.value;
}

bool Token::operator!=(const Token &t) const {
	return !(*this == t);
}
