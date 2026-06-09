#include "../../include/cli/Repl.hpp"
#include "../../include/common/error.hpp"
#include "../../include/interpreter/Runtime.hpp"
#include "../../include/interpreter/error/InterpreterError.hpp"
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <string>
#include <string_view>

Repl::Repl() {
	std::ifstream file(".history");
	if (!file.is_open()) {
		return;
	}
	std::string line;
	while (std::getline(file, line)) {
		_history.push_back(line);
	}
}

Repl::~Repl() {
	std::ofstream file(".history", std::ios::app);
	if (!file.is_open()) {
		return;
	}
	for (auto line : _history) {
		file << line << "\n";
	}
}

void Repl::run() {
	welcome_message();

	while (running) {
		std::string line = read_line("> ");
		if (line != "history") {
			_history.push_back(line);
		}
		if (is_command(line)) {
			execute_command(line);
			continue;
		}
		try {
			// Value result =
			runtime.execute(line);
			// result.print();
		} catch (const InterpreterError &e) {
			std::cout << format_error(e) << "\n";
		} catch (const std::exception &e) {
			std::cerr << "Unexpected error: " << e.what() << "\n";
		}
	}
}

std::string Repl::read_line(std::string_view prompt) {
	std::string line;

	std::cout << prompt;
	std::cout.flush();
	if (!std::getline(std::cin, line)) {
		return "quit";
	}
	return line;
}

void Repl::help() const {
	printf("usage: enter expressions and press Enter to evaluate them\n");
	printf(" commands:\n");
	printf("  help\t\tprints this menu\n");
	printf("  history\tprints command history\n");
	printf("  clear_history\tclears history\n");
	printf("  vars\t\tprints saved variables\n");
	printf("  quit\t\tquit program\n");
}

void Repl::welcome_message() const {
	printf("\tWelcome to my math interpreter\n");
	help();
	printf("\n");
}

void Repl::vars() const {
	printf("Not impemented yet\n");
}

void Repl::history() const {
	size_t count(1);
	for (auto line : _history) {
		std::cout << count++ << " " << line << std::endl;
	}
}

void Repl::clear_history() {
	_history.clear();
	std::ofstream file(".history", std::ios::out | std::ios::trunc);
}

bool Repl::is_command(std::string_view line) const {
	return commands.find(std::string(line)) != commands.end();
}

void Repl::execute_command(std::string_view command) {
	commands[std::string(command)]();
}
