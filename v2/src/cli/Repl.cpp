#include "../../include/cli/Repl.hpp"
#include "../../include/common/error.hpp"
#include "../../include/common/utils.hpp"
#include "../../include/interpreter/Runtime.hpp"
#include "../../include/interpreter/error/InterpreterError.hpp"
#include <cstddef>
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

	while (true) {
		std::string line = read_line("> ");
		_history.push_back(line);
		if (str::to_lower(line) == "quit") {
			printf("\nBye!\n");
			break;
		}
		if (handle_commands(line)) {
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
	printf("  var\t\tprints command history\n");
	printf("  quit\t\tquit program\n");
}

void Repl::welcome_message() const {
	printf("\tWelcome to my math interpreter\n");
	help();
}

void Repl::print_vars() const {
	printf("Not impemented yet\n");
}

bool Repl::handle_commands(std::string_view line) {
	if (line == "help") {
		help();
		return true;
	}
	if (line == "var") {
		print_vars();
		return true;
	}
	if (line == "history") {
		size_t count(0);
		for (auto line : _history) {
			std::cout << count++ << " " << line << std::endl;
		}
		return true;
	}
	return false;
}
