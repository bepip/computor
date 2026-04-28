#include "../../include/interpreter/Lexer.hpp"
#include <cctype>
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
	} while (t.type != TokenType::End);
	return tokens;
}

Token Lexer::nextToken() {
	skipWhiteSpace();

	if (pos >= src.size())
		return {TokenType::End, "", 0};
	char curr = currentChar();

	if (std::isdigit(curr))
		return number();

	switch (curr) {
		case '+':
			advance();
			return {TokenType::Plus, "+", 0};
		case '-':
			advance();
			return {TokenType::Minus, "-", 0};
		case '*':
			advance();
			return {TokenType::Mul, "*", 0};
		case '/':
			advance();
			return {TokenType::Div, "/", 0};
		case '(':
			advance();
			return {TokenType::LParen, "(", 0};
		case ')':
			advance();
			return {TokenType::RParen, ")", 0};
	}
	advance();
	return {TokenType::Invalid, std::string(1, curr), 0};
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
		TokenType::Number,
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
