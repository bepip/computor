#pragma once

#include <string>
#include <string_view>
#include <vector>

enum class token_type {
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
	token_type type;
	std::string lexeme;
	double value;

	std::string to_string() const;
	bool operator==(const Token &t) const;
	bool operator!=(const Token &t) const;
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
