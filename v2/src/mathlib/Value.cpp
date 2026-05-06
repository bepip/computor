#include "../../include/mathlib/Value.hpp"

void Value::print() const {
	std::visit(Value::Visitor{}, data);
}
