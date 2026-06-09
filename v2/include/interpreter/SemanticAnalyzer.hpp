#pragma once
#include "AST.hpp"
#include "Context.hpp"

class SemanticAnalyzer {
  private:
	Context &context;

  public:
	explicit SemanticAnalyzer(Context &context) :
		context(context) {}

	void analyze(const Statement *stmt);

  private:
	void analyze_statement(const Statement *stmt);
	void analyze_expression(const Expression *stmt);
};
