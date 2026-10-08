#include "../../include/mathlib/Value.hpp"
#include <iostream>

void Value::print() const {
	std::visit([](const auto &value) { std::cout << value; }, data);
}

void Value::println() const {
	std::visit([](const auto &value) { std::cout << value << std::endl; }, data);
}
