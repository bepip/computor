#pragma once

#include "../mathlib/Value.hpp"
#include "AST.hpp"
#include <string>
#include <unordered_map>

class Context {
  public:
	std::unordered_map<std::string, Value> variables;
	// TODO: crate a function class that will hold all the info for the functions map
	std::unordered_map<std::string, const FunctionDefStmt *> functions;

	Value get_var(const std::string &key);
	Value get_func(const std::string &key);
};
