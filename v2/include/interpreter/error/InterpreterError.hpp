#pragma once

#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

class InterpreterError : public std::runtime_error {
  private:
	std::string _stage;

  public:
	InterpreterError(std::string_view stage, std::string message) :
		std::runtime_error(std::move(message)),
		_stage(std::move(stage)) {}

	const std::string &stage() const { return _stage; }
};
