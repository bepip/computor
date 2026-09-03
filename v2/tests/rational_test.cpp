#include "../include/mathlib/Rational.hpp"
#include "tests.hpp"
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

// TODO:: find a way to output the tests better than this
namespace {

	struct test_case {
		std::string name;
		Rational input;
		Rational expected;
	};

	void print_test(size_t count, std::string_view msg, bool passed) {
		std::cout << "[" << count << "]" << (passed ? "✅" : "❌") << ": '" << msg << "'";
		std::cout << std::endl;
	}

	std::vector<test_case> setup() {
		std::vector<test_case> tests;
		tests.reserve(20);

		auto add = [&](std::string_view name, Rational input, Rational rat) {
			tests.emplace_back(test_case{std::string(name), input, rat});
		};

		add("Rational(2, 4) == Rational(1, 2)", Rational(2, 4), Rational(1, 2));
		add("Rational(1, -1) == Rational(-1, 1)", Rational(-1, 1), Rational(1, -1));
		add("Rational(1, -1) + Rational (1, 1) = Rational(0, 1)",
			Rational(-1, 1) + Rational(1, 1), Rational(0, 1));
		return tests;
	}

	bool test_rational_case(const Rational &input, const Rational &expected) {
		return input == expected;
	}

	test_result rational_tester() {
		const auto &tests = setup();
		size_t i = 0;
		size_t failed = 0;

		for (const auto &[name, input, expected] : tests) {
			const bool &res = test_rational_case(input, expected);
			if (!res) {
				++failed;
			}
			print_test(++i, name, res);
		}
		return {failed, tests.size()};
	}
} // namespace

test_result test_rational() {
	print_title("Rationals");
	const auto &result = rational_tester();
	print_result(result);
	return result;
}
