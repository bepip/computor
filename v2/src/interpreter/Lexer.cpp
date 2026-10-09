#include "../../include/interpreter/Lexer.hpp"
#include "../../include/interpreter/error/InterpreterError.hpp"
#include <cctype>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

std::vector<Token> Lexer::tokenize(std::string_view input) {
	src = input;
	pos = 0;
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
		return {token_type::End, ""};
	char curr = current_char();

	if (std::isdigit(curr))
		return number();
	if (std::isalpha(curr))
		return identifier();

	switch (curr) {
		case '+':
			advance();
			return {token_type::Plus, "+"};
		case '-':
			advance();
			return {token_type::Minus, "-"};
		case '*':
			advance();
			return {token_type::Mul, "*"};
		case '/':
			advance();
			return {token_type::Div, "/"};
		case '^':
			advance();
			return {token_type::Power, "^"};
		case '%':
			advance();
			return {token_type::Mod, "%"};
		case '(':
			advance();
			return {token_type::LParen, "("};
		case ')':
			advance();
			return {token_type::RParen, ")"};
		case '=':
			advance();
			return {token_type::Assign, "="};
		case '?':
			advance();
			return {token_type::Query, "?"};
	}
	throw InterpreterError("Lexer", "Invalid token: " + std::string(1, curr));
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
		throw InterpreterError("Lexer", "Invalid token: " + num_str);
	}
	return {
		token_type::Number,
		num_str
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
		return {token_type::Imag, str};
	return {token_type::Ident, str};
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
		case token_type::Power:
			return "POWER('" + lexeme + "')";
		case token_type::Mod:
			return "MOD_SIGN('" + lexeme + "')";
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
	}
	return "INVALID_TOKEN('" + lexeme + "')";
}

void Token::print() const {
	std::cout << this->to_string() << std::endl;
}

bool Token::operator==(const Token &t) const {
	return type == t.type && lexeme == t.lexeme;
}

bool Token::operator!=(const Token &t) const {
	return !(*this == t);
}
