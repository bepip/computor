#include "../../include/common/error.hpp"
#include "../../include/interpreter/error/InterpreterError.hpp"
#include <string>

std::string format_error(const InterpreterError& e) {
	return e.stage() + " error: " + e.what();
}
