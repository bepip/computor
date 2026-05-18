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
		t = next_token();
		tokens.push_back(t);
	} while (t.type != token_type::End);
	return tokens;
}

Token Lexer::next_token() {
	skip_white_space();

	if (pos >= src.size())
		return {token_type::End, "", 0};
	char curr = current_char();

	if (std::isdigit(curr))
		return number();
	if (std::isalpha(curr))
		return identifier();

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
		case '=':
			advance();
			return {token_type::Assign, "=", 0};
	}
	advance();
	return {token_type::Invalid, std::string(1, curr), 0};
}

void Lexer::advance() {
	++pos;
}

Token Lexer::number() {
	size_t start = pos;
	bool seen_dot = false;

	while (pos < src.size()) {
		char c = src[pos];

		if (isdigit(c)) {
			pos++;
		} else if (c == '.') {
			if (seen_dot)
				break;
			seen_dot = true;
			pos++;
		} else {
			break;
		}
	}
	std::string num_str = src.substr(start, pos - start);
	if (num_str == "." || num_str.back() == '.') {
		return {token_type::Invalid, num_str, 0};
	}
	return {
		token_type::Number,
		num_str,
		std::stod(num_str),
	};
}

Token Lexer::identifier() {
	size_t start = pos;

	while (pos < src.size()) {
		char c = src[pos];

		if (std::isalpha(c)) {
			pos++;
		} else {
			break;
		}
	}
	std::string str = src.substr(start, pos - start);
	if (str == "i" || str == "I")
		return {token_type::Imag, str, 0};
	return {token_type::Ident, str, 0};
}

void Lexer::skip_white_space() {
	while (pos < src.size() && isspace(src[pos])) {
		pos++;
	}
}

char Lexer::current_char() const {
	return src[pos];
}

std::string Token::to_string() const {
	switch (type) {
		case token_type::Ident:
			return "IDENT('" + lexeme + "')";
		case token_type::Imag:
			return "IMAG('" + lexeme + "')";
		case token_type::Assign:
			return "ASSIGN('" + lexeme + "')";
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
		case token_type::Query:
			return "QUERY('" + lexeme + "')";
		case token_type::End:
			return "EOF";
		case token_type::Invalid:
			return "INVALID_TOKEN('" + lexeme + "')";
	}
	return "INVALID_TOKEN('" + lexeme + "')";
}

void Token::print() const {
	std::cout << this->to_string() << std::endl;
}

bool Token::operator==(const Token &t) const {
	return type == t.type && lexeme == t.lexeme && value == t.value;
}

bool Token::operator!=(const Token &t) const {
	return !(*this == t);
}
