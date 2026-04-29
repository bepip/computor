#include "../include/common/utils.hpp"
#include "tests.hpp"
#include <iostream>
#include <string_view>
#include <vector>

namespace {
	void help() {
		std::cout << "To run Lexer tests run with -l" << std::endl;
	}
} // namespace

int main(int ac, char *av[]) {
	// run all tests
	if (ac == 1) {
		test_lexer();
	} else {
		std::vector<std::string_view> args(av + 1, av + ac);
		if (contains(args, "-h") || contains(args, "--help")) {
			help();
			return 0;
		}
		if (contains(args, "-l"))
			test_lexer();
	// TODO: catch tests results struct to print end result
	}
	return 0;
}
