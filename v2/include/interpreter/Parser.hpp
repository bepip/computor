#pragma once

#include "AST.hpp"
#include "Lexer.hpp"
#include <cstddef>
#include <vector>

class Parser {
  private:
	std::vector<Token> tokens;
	size_t current;

  public:
	Parser(std::vector<Token> tokens);
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

	Token peek(size_t offset = 0) const;
	Token advance();
	bool match(token_type t);
};
