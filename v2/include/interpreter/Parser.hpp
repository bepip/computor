#pragma once

#include "AST.hpp"
#include "Lexer.hpp"
#include <cstddef>
#include <vector>

class Parser {
  private:
	std::vector<Token> tokens;
	size_t pos;

  public:
	explicit Parser(std::vector<Token> tokens);
	stmt_ptr parse();

  private:
	stmt_ptr parse_statement();
	stmt_ptr parse_assignment();
	stmt_ptr parse_function_definition();
	stmt_ptr parse_expression_statement();
	stmt_ptr parse_query_statement();

	expr_ptr parse_expression();
	expr_ptr parse_term();
	expr_ptr parse_unary();
	expr_ptr parse_factor();

	const Token &peek(size_t offset = 0) const;
	const Token &previous() const;
	const Token &advance();
	bool is_at_end() const;
	const Token &consume(token_type type, std::string_view message);

	bool match(token_type t);
};
