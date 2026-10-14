#include "../../include/interpreter/AST.hpp"
#include <optional>
#include <string>

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
