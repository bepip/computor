#include "../include/common/utils.hpp"
#include "tests.hpp"
#include <cstddef>
#include <iostream>
#include <optional>
#include <string_view>
#include <vector>

namespace {

	void help() {
		std::cout << "run lexer tests with -l." << std::endl;
		std::cout << "run parser tests with -p." << std::endl;
	}

	void run_test(test_result &results, test_result (*f)()) {
		results += f();
	}

	void run_all_tests(test_result &results) {
		run_test(results, test_lexer);
		// run_test(test_parser);
	}

	void run_tests_with_opt(test_result &results, const std::vector<std::string_view> &args) {
		if (contains(args, "-l")) {
			run_test(results, test_lexer);
		}
		// if (contains(args, "-p")) {
		// 	run_test(results, test_parser);
		// }
	}

	std::optional<test_result> handle_tests(int ac, char *av[]) {
		test_result results = {};

		if (ac == 1) {
			run_all_tests(results);
		} else {
			std::vector<std::string_view> args(av + 1, av + ac);
			if (contains(args, "-h") || contains(args, "--help")) {
				help();
				return std::nullopt;
			}
			run_tests_with_opt(results, args);
		}
		return results;
	}

} // namespace

int main(int ac, char *av[]) {
	auto result = handle_tests(ac, av);
	if (result.has_value()) {
		size_t total = result.value().total;
		size_t failed = result.value().failed;
		// TODO: catch tests results struct to print end result
		std::cout << "-------------------------------------------" << std::endl;
		std::cout << "Tests: " << total << ", Passed: " << total - failed << std::endl;
		return failed > 0 ? 1 : 0;
	}
	return 0;
}
