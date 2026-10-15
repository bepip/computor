#include "../../include/interpreter/Context.hpp"
#include "../../include/common/utils.hpp"
#include <optional>
#include <string>

std::optional<Value> Context::get_var(const std::string &key) const{
	auto it = variables.find(str::to_lower(key));
	if (it != variables.end()) {
		return it->second;
	}
	return std::nullopt;
}

const Function *Context::get_func(const std::string &key) const{
	auto it = functions.find(str::to_lower(key));
	if (it != functions.end()) {
		return &it->second;
	}
	return nullptr;
}

void Context::add_var(const std::string &key, Value value) {
	variables.insert_or_assign(str::to_lower(key), std::move(value));
}

void Context::add_func(const std::string &key, Function func) {
	functions.insert_or_assign(str::to_lower(key), std::move(func));
}
