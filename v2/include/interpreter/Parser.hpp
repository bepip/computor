#pragma once

#include "AST.hpp"
#include "Lexer.hpp"
#include <cstddef>
#include <vector>

class Parser {
  private:
	std::vector<Token> tokens = {};
	size_t pos = 0;

  public:
	[[nodiscard]] stmt_ptr parse(std::vector<Token> tokens);

  private:
	[[nodiscard]] stmt_ptr parse_statement();
	[[nodiscard]] stmt_ptr parse_assignment_or_function_definition(expr_ptr left, expr_ptr right);

	[[nodiscard]] expr_ptr parse_expression();
	[[nodiscard]] expr_ptr parse_term();
	[[nodiscard]] expr_ptr parse_unary();
	[[nodiscard]] expr_ptr parse_power();
	[[nodiscard]] expr_ptr parse_factor();
	[[nodiscard]] expr_ptr parse_function_call(std::string_view name);

	[[nodiscard]] const Token &peek(size_t offset = 0) const;
	[[nodiscard]] const Token &previous() const;
	[[nodiscard]] bool is_at_end() const;
	const Token &consume(token_type type, std::string_view message);

	[[nodiscard]] bool match(token_type t);

	[[nodiscard]] bool is_implicit_multiplication() const;
};
