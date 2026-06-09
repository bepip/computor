#pragma once

#include "../../include/mathlib/Value.hpp"
#include "Evaluator.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "SemanticAnalyzer.hpp"
#include <string>
#include <string_view>
#include <vector>

class Runtime {
  public:
	Runtime();
	Value execute(std::string_view line);

  private:
	Context context;
	Lexer lexer;
	Parser parser;
	SemanticAnalyzer semantic;
	Evaluator evaluator;
	std::vector<std::string> _history;
};
