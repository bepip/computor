#pragma once

#include "AST.hpp"
#include "Context.hpp"

class Evaluator {
  private:
	Context &context;

  public:
	explicit Evaluator(Context &context) :
		context(context) {}

	void evaluate(const Statement *stmt);
};
