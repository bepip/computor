#include "../../include/mathlib/Value.hpp"
#include <iostream>
#include <sstream>

void Value::print() const {
	std::visit([](const auto &value) { std::cout << value; }, data);
}

void Value::println() const {
	std::visit([](const auto &value) { std::cout << value << std::endl; }, data);
}

std::string Value::to_string() const {
	std::ostringstream oss;
	std::visit([&oss](const auto &value) { oss << value; }, data);
	return oss.str();
}
