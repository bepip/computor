#include "../../include/interpreter/Runtime.hpp"
// #include "../../include/interpreter/ASTPrinter.hpp"
#include "../../include/interpreter/Lexer.hpp"
#include "../../include/interpreter/Parser.hpp"
#include "../../include/mathlib/Value.hpp"
#include <string_view>

Runtime::Runtime() :
	evaluator(context) {}

Value Runtime::execute(std::string_view line) {
	auto tokens = lexer.tokenize(line);

	auto ast = parser.parse(tokens);
	// ASTPrinter::print(ast.get());

	return evaluator.evaluate(ast.get());
}

Context Runtime::get_context() const {
	return context;
}
