#pragma once

#include "AST.hpp"
#include <string>
#include <unordered_map>

class Context {
  public:
	std::unordered_map<std::string, expr_ptr> variables;
	std::unordered_map<std::string, const FunctionDefStmt *> functions;
};
