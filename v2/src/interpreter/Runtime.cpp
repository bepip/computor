#include "../../include/interpreter/Runtime.hpp"
#include "../../include/interpreter/Lexer.hpp"
#include "../../include/mathlib/Value.hpp"
#include <string_view>

Value Runtime::execute(std::string_view line) {
	Lexer lexer(line);
	auto tokens = lexer.tokenize();

	// Parser parser(tokens);
	// ASTNode* ast = parser.parse();
	//
	// SemanticAnalyzer sem(symbols);
	// sem.check(ast);
	//
	// Evaluator eval(symbols);
	// return eval.evaluate();
	return {};
}
