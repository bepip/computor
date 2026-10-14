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

void print_test(size_t count, std::string_view msg, bool passed) {
	std::cout << "[" << count << "]" << (passed ? "✅" : "❌") << ": '" << msg << "'";
	std::cout << std::endl;
}

void print_title(std::string_view title) {
	std::cout << GREEN << title << NC << std::endl << std::endl;
}

void print_result(test_result result) {
	const size_t total = result.total;
	const size_t failed = result.failed;
	const size_t passed = total - failed;

	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "[" << passed << "/" << total << "] "
			  << (failed == 0 ? "Passed ✅" : "Failed ❌") << std::endl;
}

int print_final_result(test_result result) {
	const size_t total = result.total;
	const size_t failed = result.failed;
	const size_t passed = total - failed;
	std::cout << "===========================================" << std::endl;
	std::cout << "Total:\n";
	std::cout << "[" << passed << "/" << total << "] "
			  << (failed == 0 ? "Passed ✅" : "Failed ❌") << std::endl;
	return failed > 0 ? 1 : 0;
}

void clear_screen() {
	std::cout << "\x1b[H\x1b[2J" << std::flush;
}
