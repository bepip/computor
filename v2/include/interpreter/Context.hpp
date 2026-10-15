#pragma once

#include "../mathlib/Function.hpp"
#include "../mathlib/Value.hpp"
#include <string>
#include <unordered_map>

class Context {
  public:
	std::unordered_map<std::string, Value> variables;
	std::unordered_map<std::string, Function> functions;

	void add_var(const std::string &key, Value value);
	void add_func(const std::string &key, Function func);
	std::optional<Value> get_var(const std::string &key);
	Function* get_func(const std::string &key);
};
