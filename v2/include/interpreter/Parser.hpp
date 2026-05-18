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
	[[nodiscard]] stmt_ptr parse();

  private:
	[[nodiscard]] stmt_ptr parse_statement();
	[[nodiscard]] stmt_ptr parse_assignment();
	[[nodiscard]] stmt_ptr parse_function_definition();
	[[nodiscard]] stmt_ptr parse_expression_statement();
	[[nodiscard]] stmt_ptr parse_query_statement();

	[[nodiscard]] expr_ptr parse_expression();
	[[nodiscard]] expr_ptr parse_term();
	[[nodiscard]] expr_ptr parse_unary();
	[[nodiscard]] expr_ptr parse_factor();

	[[nodiscard]] const Token &peek(size_t offset = 0) const;
	[[nodiscard]] const Token &previous() const;
	[[nodiscard]] bool is_at_end() const;
	const Token &consume(token_type type, std::string_view message);

	[[nodiscard]] bool match(token_type t);

	[[nodiscard]] bool is_assignment() const;
	[[nodiscard]] bool is_function_definition() const;

	[[nodiscard]] bool is_implicit_multiplication() const;
};
