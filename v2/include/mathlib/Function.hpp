#pragma once

#include "../interpreter/AST.hpp"
#include <string>
#include <utility>

class Function {
  private:
	std::string _parameter;
	expr_ptr _body;

  public:
	Function(std::string parameter, expr_ptr body) :
		_parameter(std::move(parameter)),
		_body(std::move(body)) {}
};
