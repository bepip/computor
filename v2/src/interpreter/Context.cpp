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
