#pragma once

#include <string>
#include <string_view>
#include <vector>

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
	std::vector<Token> tokenize();

  private:
	std::string src;
	size_t pos;

	char currentChar() const;
	void advance();
	void skipWhiteSpace();
	Token number();
	Token nextToken();
};
