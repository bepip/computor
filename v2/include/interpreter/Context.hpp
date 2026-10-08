#pragma once

#include "../mathlib/Value.hpp"
#include "AST.hpp"
#include <optional>
#include <string>
#include <unordered_map>

class Context {
  public:
	std::unordered_map<std::string, Value> variables;
	// TODO: crate a function class that will hold all the info for the functions map
	std::unordered_map<std::string, const FunctionDefStmt *> functions;

	std::optional<Value> get_var(const std::string &key);
	std::optional<const FunctionDefStmt *> get_func(const std::string &key);
};
