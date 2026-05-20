#pragma once

#include "AST.hpp"

class ASTPrinter {
  public:
	static void print(const Statement *stmt);

  private:
	ASTPrinter() = delete;
	static void print_statement(const Statement *stmt, size_t indent);
	static void print_expression(const Expression *expr, size_t indent);

	static void indent(size_t level);
};
