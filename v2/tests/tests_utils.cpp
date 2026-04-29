#include "tests.hpp"
#include <iostream>
#include <string_view>

void print_test(size_t count, std::string_view msg, const case_result &cr) {
	std::cout << "[" << count << "]" << (cr.passed ? "✅" : "❌") << ": '" << msg << "'";
	if (!cr.passed) {
		std::cout << " -> Error at index " << cr.fail_index;
	}
	std::cout << std::endl;
}

void print_title(std::string_view title) {
	std::cout << "Testing " << title << std::endl << std::endl;
}

void print_result(size_t failed, size_t total) {
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "[" << total - failed << "/" << total << "] "
			  << (failed == 0 ? "Passed ✅" : "Failed ❌") << std::endl;
}
