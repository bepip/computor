#pragma once

#include "../interpreter/error/InterpreterError.hpp"
#include <string>

std::string format_error(const InterpreterError &e);
