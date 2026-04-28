#pragma once

#include <string>
#include <string_view>

enum class TokenType {
	Number,
	Plus,
	Minus,
	Mul,
	Div,
	LParen,
	RParen,
	End,
	Invalid
};

struct Token {
	TokenType type;
	std::string lexeme;
	double value;
};

class Lexer {
  public:
	Lexer(std::string_view input);
	Token nextToken();
};
