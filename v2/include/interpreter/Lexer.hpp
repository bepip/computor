#pragma once

#include <string>
#include <string_view>
#include <vector>

enum class token_type {
	Ident,
	Assign,
	Imag,
	Number,
	Plus,
	Minus,
	Mul,
	Div,
	Power,
	LParen,
	RParen,
	Query,
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
	void print() const;
};

class Lexer {
  private:
	std::string src;
	size_t pos;

  public:
	explicit Lexer(std::string_view input);
	std::vector<Token> tokenize();

  private:
	char current_char() const;
	void advance();
	void skip_white_space();
	Token number();
	Token identifier();
	Token next_token();
};
