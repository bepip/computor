#include "../../include/interpreter/AST.hpp"
#include <optional>
#include <string>

Rational NumberExpr::as_rational() const {
	if (is_literal())
		return Rational(std::get<std::string>(value));
	const auto val = std::get<Value>(value);
	if (!val.is<Rational>()) {
		throw std::invalid_argument("Functions only take Rationals");
	}
	return val.get<Rational>();
}

bool NumberExpr::is_literal() const {
	return std::holds_alternative<std::string>(value);
}

bool NumberExpr::is_value() const {
	return std::holds_alternative<Value>(value);
}

std::optional<operation> operation_from_char(char c) {
	switch (c) {
		case '+':
			return operation::Add;
		case '-':
			return operation::Sub;
		case '%':
			return operation::Mod;
		case '*':
			return operation::Mul;
		case '/':
			return operation::Div;
		case '^':
			return operation::Pow;
		case 'x':
			return operation::MatrixMul;
	};
	return std::nullopt;
}

std::string operation_to_string(operation op) {
	switch (op) {
		case operation::Add:
			return "+";
		case operation::Sub:
			return "-";
		case operation::Mod:
			return "%";
		case operation::Mul:
			return "*";
		case operation::Div:
			return "/";
		case operation::Pow:
			return "^";
		case operation::MatrixMul:
			return "**";
	};
	return "";
}
