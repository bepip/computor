#pragma once
#include "../../include/interpreter/Runtime.hpp"
#include <cstdio>
#include <functional>
#include <string>
#include <string_view>
#include <unordered_map>

class Repl {
  private:
	bool running = true;
	std::vector<std::string> _history;
	std::unordered_map<std::string, std::function<void()>> commands = {
		{"help", [this]() { help(); }},
		{"vars", [this]() { vars(); }},
		{"history", [this]() { history(); }},
		{"clear_history", [this]() { clear_history(); }},
		{"help", [this]() { help(); }},
		{"quit",
		 [this]() {
			 printf("\nbye\n");
			 running = false;
		 }},
	};
	Runtime runtime;

  public:
	Repl();
	~Repl();
	void run();

  private:
	std::string read_line(std::string_view prompt);
	void help() const;
	void vars() const;
	void clear_history();
	void history() const;
	void welcome_message() const;

	[[nodiscard]]
	bool is_command(std::string_view line) const;
	void execute_command(std::string_view command);
};
