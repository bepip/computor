#pragma once

#include "../interpreter/AST.hpp"
#include <string>
#include <utility>

class Context;

class Function {
  private:
	std::string _parameter;
	expr_ptr _body;

  public:
	Function(std::string parameter, expr_ptr body) :
		_parameter(std::move(parameter)),
		_body(std::move(body)) {}

	void simplifiy(const Context &context);

	std::string to_string() const;

	const std::string &parameter() const;
	const Expression *body() const;
};
