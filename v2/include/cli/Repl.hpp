#pragma once
#include "../../include/interpreter/Runtime.hpp"
#include <string>
#include <string_view>

class Repl {
  private:
	std::vector<std::string> _history;
	Runtime runtime;

  public:
	Repl();
	~Repl();
	void run();

  private:
	std::string read_line(std::string_view prompt);
	void help() const;
	void print_vars() const;
	void welcome_message() const;
	bool handle_commands(std::string_view line);
};
