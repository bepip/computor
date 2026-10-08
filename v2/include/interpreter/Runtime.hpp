#pragma once

#include "../../include/mathlib/Value.hpp"
#include "Evaluator.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include <string>
#include <string_view>
#include <vector>

class Runtime {
  public:
	Runtime();
	Value execute(std::string_view line);

	Context get_context() const;

  private:
	Context context;
	Lexer lexer;
	Parser parser;
	Evaluator evaluator;
	std::vector<std::string> _history;
};
