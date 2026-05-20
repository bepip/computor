#include "../../include/common/utils.hpp"
#include "../../include/interpreter/Runtime.hpp"
#include <iostream>
#include <string>

namespace {
	std::string read_line(const std::string &prompt) {
		std::string line;

		std::cout << prompt;
		std::cout.flush();
		if (!std::getline(std::cin, line)) {
			return "quit";
		}
		return line;
	}

	void show_help() {
		printf("Not implemented yet\n");
	}

	void welcome_message() {
		printf("\tWelcome to my math interpreter\n");
	}
} // namespace

void start_repl() {
	Runtime runtime;
	welcome_message();

	while (true) {
		std::string line = read_line("> ");
		if (str::to_lower(line) == "quit" || str::to_lower(line) == "q" ||
			str::to_lower(line) == "exit") {
			printf("\nBye!\n");
			break;
		}
		if (line == "help") {
			show_help();
			continue;
		}
		try {
			// Value result =
			runtime.execute(line);
			// result.print();
		} catch (const std::exception &e) {
			std::cout << "Error: " << e.what() << std::endl;
			// print_error(e.what());
		}
	}
}
