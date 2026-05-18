#include "../../include/interpreter/Runtime.hpp"
#include "../../include/interpreter/Lexer.hpp"
#include "../../include/interpreter/Parser.hpp"
#include "../../include/mathlib/Value.hpp"
#include <string_view>

Value Runtime::execute(std::string_view line) {
	Lexer lexer(line);
	auto tokens = lexer.tokenize();

	for (const auto &token : tokens) {
		token.print();
	}

	Parser parser(tokens);
	auto ast = parser.parse();
	ASTPrinter::print(ast.get());
	//
	// SemanticAnalyzer sem(symbols);
	// sem.check(ast);
	//
	// Evaluator eval(symbols);
	// return eval.evaluate();
	return {};
}
