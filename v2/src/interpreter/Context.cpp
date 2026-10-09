#include "../../include/interpreter/Context.hpp"
#include <optional>
#include <string>

std::optional<Value> Context::get_var(const std::string &key) {
	auto it = variables.find(key);
	if (it != variables.end()) {
		return it->second;
	}
	return std::nullopt;
}

std::optional<const FunctionDefStmt *> Context::get_func(const std::string &key) {
	auto it = functions.find(key);
	if (it != functions.end()) {
		return it->second;
	}
	return std::nullopt;
}

void Context::add_var(const std::string &key, const Value &value) {
	variables.insert_or_assign(key, value);
}

void Context::add_func(const std::string &key, const FunctionDefStmt *func) {
	functions.insert_or_assign(key, func);
}
