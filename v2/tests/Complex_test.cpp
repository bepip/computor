
#include "../include/mathlib/Complex.hpp"
#include "../include/mathlib/Complex.hpp"
#include "tests.hpp"
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

namespace {
	enum sign {
		equal,
		not_equal,
		greater,
		greater_eq,
		less,
		less_eq,
	};

	struct test_case {
		std::string name;
		Complex input;
		Complex expected;
		sign type;
	};

	void print_test(size_t count, std::string_view msg, bool passed) {
		std::cout << "[" << count << "]" << (passed ? "✅" : "❌") << ": '" << msg << "'";
		std::cout << std::endl;
	}

	std::vector<test_case> setup() {
		std::vector<test_case> tests;
		tests.reserve(20);

		auto add = [&](std::string_view name, Complex input, Rational rat, sign opt) {
			tests.emplace_back(test_case{std::string(name), input, rat, opt});
		};

		return tests;
	}

	// enum sign {
	// 	equal,
	// 	not_equal,
	// 	greater,
	// 	greater_eq,
	// 	less,
	// 	less_eq,
	// };

	bool test_complex_case(const test_case &c) {
		Complex input = c.input;
		Complex expected = c.expected;
		switch (c.type) {
			case equal:
				return input == expected;
			case not_equal:
				return input != expected;
			case greater:
				return input > expected;
			case greater_eq:
				return input >= expected;
			case less:
				return input < expected;
			case less_eq:
				return input <= expected;
		}
		return false;
	}

	test_result complex_tester() {
		const auto &tests = setup();
		size_t i = 0;
		size_t failed = 0;

		for (const auto &test_case : tests) {
			const bool &res = test_complex_case(test_case);
			if (!res) {
				++failed;
			}
			print_test(++i, test_case.name, res);
		}
		return {failed, tests.size()};
	}
} // namespace

test_result test_complex() {
	print_title("Complex");
	const auto &result = complex_tester();
	print_result(result);
	return result;
}
