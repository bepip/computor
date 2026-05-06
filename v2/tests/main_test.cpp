#include "../include/common/utils.hpp"
#include "tests.hpp"
#include <cstddef>
#include <iostream>
#include <string_view>
#include <vector>

namespace {

	size_t total = 0, failed = 0;

	void help() {
		std::cout << "To run Lexer tests run with -l" << std::endl;
	}

	void run_test(test_result (*f)()) {
		const auto &[fail, tot] = f();
		failed += fail;
		total += tot;
	}

	void run_all_tests() {
		run_test(test_lexer);
	}
} // namespace

int main(int ac, char *av[]) {
	// run all tests
	if (ac == 1) {
		run_all_tests();
	} else {
		std::vector<std::string_view> args(av + 1, av + ac);
		if (contains(args, "-h") || contains(args, "--help")) {
			help();
			return 0;
		}
		if (contains(args, "-l")) {
			run_test(test_lexer);
		}
	}
	// TODO: catch tests results struct to print end result
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Tests: " << total << ", Passed: " << total - failed << std::endl;
	return failed > 0 ? 1 : 0;
}
