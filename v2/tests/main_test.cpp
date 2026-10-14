#include "../include/common/utils.hpp"
#include "tests.hpp"
#include <functional>
#include <iostream>
#include <optional>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace {

	static const std::unordered_map<std::string, std::function<test_result()>> tests{
		{"runtime", test_runtime},
		{"matrix", test_matrix},
		{"complex", test_complex},
		{"rational", test_rational},
		{"lexer", test_lexer},
	};

	void help() {
		std::cout << "usage: ./tester [-option]" << std::endl;
		std::cout << "   -l : lexer" << std::endl;
		std::cout << "   -r : runtime" << std::endl;
		std::cout << "   -m : math" << std::endl;
	}

	void run_test(test_result &results, test_result (*f)()) {
		results += f();
	}

	void run_all_tests(test_result &results) {
		for (const auto &pair : tests) {
			results += pair.second();
			std::cout << "-------------------------------------------" << std::endl;
		}
	}

	void run_tests_with_opt(test_result &results,
							const std::vector<std::string_view> &args) {
		if (contains(args, "-l")) {
			run_test(results, test_lexer);
		}
		if (contains(args, "-m")) {
			run_test(results, test_rational);
			run_test(results, test_complex);
			run_test(results, test_matrix);
		}
		if (contains(args, "-r")) {
			run_test(results, test_runtime);
		}
	}

	std::optional<test_result> test_handler(int ac, char *av[]) {
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
	auto result = test_handler(ac, av);
	if (result.has_value()) {
		return print_final_result(result.value());
	}
	return 0;
}
