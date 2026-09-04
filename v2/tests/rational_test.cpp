#include "../include/mathlib/Rational.hpp"
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
		Rational input;
		Rational expected;
		sign type;
	};

	void print_test(size_t count, std::string_view msg, bool passed) {
		std::cout << "[" << count << "]" << (passed ? "✅" : "❌") << ": '" << msg << "'";
		std::cout << std::endl;
	}

	std::vector<test_case> setup() {
		std::vector<test_case> tests;
		tests.reserve(20);

		auto add = [&](std::string_view name, Rational input, Rational rat, sign opt) {
			tests.emplace_back(test_case{std::string(name), input, rat, opt});
		};

		add("Rational(2, 4) == Rational(1, 2)", Rational(2, 4), Rational(1, 2),
			sign::equal);
		add("Rational(-2, 4) == Rational(1, -2)", Rational(-2, 4), Rational(1, -2),
			sign::equal);
		add("Rational(0, 4) == Rational(0, 2)", Rational(0, 4), Rational(0, 2),
			sign::equal);
		add("Rational(1, -1) == Rational(-1, 1)", Rational(-1, 1), Rational(1, -1),
			sign::equal);
		add("Rational(1, 4) != Rational(1, 2)", Rational(1, 4), Rational(1, 2),
			sign::not_equal);
		add("Rational(3, 4) != Rational(1, 2)", Rational(3, 4), Rational(1, 2),
			sign::not_equal);
		add("Rational(1, 4) < Rational(1, 2)", Rational(1, 4), Rational(1, 2),
			sign::less);
		add("Rational(-1, 4) < Rational(1, 2)", Rational(-1, 4), Rational(1, 2),
			sign::less);
		add("Rational(2, 4) <= Rational(1, 2)", Rational(2, 4), Rational(1, 2),
			sign::less_eq);
		add("Rational(-2, 4) <= Rational(1, 2)", Rational(-2, 4), Rational(1, 2),
			sign::less_eq);
		add("Rational(2, 4) >= Rational(1, 2)", Rational(2, 4), Rational(1, 2),
			sign::greater_eq);
		add("Rational(2, 4) >= Rational(-1, 2)", Rational(2, 4), Rational(-1, 2),
			sign::greater_eq);
		add("Rational(-1, 1) + Rational(1, 1) == Rational(0, 1)",
			Rational(-1, 1) + Rational(1, 1), Rational(0, 1), sign::equal);
		add("Rational(-1, 1) + Rational(59, 2) == Rational(57, 2)",
			Rational(-1, 1) + Rational(1, 1), Rational(0, 1), sign::equal);
		add("Rational(-1, 1) - Rational(1, 1) == Rational(-2, 1)",
			Rational(-1, 1) - Rational(1, 1), Rational(-2, 1), sign::equal);
		add("Rational(-2, -61) - Rational(1, 122) == Rational(3, 122)",
			Rational(-2, -61) - Rational(1, 122), Rational(3, 122), sign::equal);
		add("Rational(-1, 1) * Rational(3, 1) == Rational(-3, 1)",
			Rational(-1, 1) * Rational(3, 1), Rational(-3, 1), sign::equal);
		add("Rational(-2, 8) * Rational(-3, 9) == Rational(6, 72)",
			Rational(-2, 8) * Rational(-3, 9), Rational(6, 72), sign::equal);
		add("Rational(-1, 3) * Rational(-3, 1) == Rational(1, 1)",
			Rational(-1, 3) * Rational(-3, 1), Rational(1, 1), sign::equal);
		add("Rational(-1, 1) / Rational(3, 1) == Rational(-1, 3)",
			Rational(-1, 1) / Rational(3, 1), Rational(-1, 3), sign::equal);
		add("Rational(-1, 1) / Rational(-3, 1) == Rational(1, 3)",
			Rational(-1, 1) / Rational(-3, 1), Rational(1, 3), sign::equal);
		add("Rational(-2, 1) / Rational(-1, 8) == Rational(16, 1)",
			Rational(-2, 1) / Rational(-1, 8), Rational(16, 1), sign::equal);
		add("-Rational(-2, 1) == Rational(2, 1)", -Rational(-2, 1), Rational(2, 1),
			sign::equal);
		add("-Rational(-2, -4) == Rational(-1, 2)", -Rational(-2, -4), Rational(-1, 2),
			sign::equal);
		add("(Rational(-2, -4) += Rational(-1, 2)) == Rational(0, 1)",
			Rational(-2, -4) += Rational(-1, 2), Rational(0, 1), sign::equal);
		add("(Rational(-2, -4) += Rational(-1, 2)) != Rational(2, 1)",
			Rational(-2, -4) += Rational(-1, 2), Rational(2, 1), sign::not_equal);
		add("(Rational(-2, -4) -= Rational(-1, 2)) == Rational(1, 1)",
			Rational(-2, -4) -= Rational(-1, 2), Rational(1, 1), sign::equal);
		add("(Rational(-2, -4) -= Rational(-1, 2)) != Rational(-1, 1)",
			Rational(-2, -4) -= Rational(-1, 2), Rational(-1, 1), sign::not_equal);
		add("(Rational(-2, -4) *= Rational(-1, 2)) == Rational(-1, 4)",
			Rational(-2, -4) *= Rational(-1, 2), Rational(-1, 4), sign::equal);
		add("(Rational(-2, -4) *= Rational(-1, 2)) != Rational(-1, 1)",
			Rational(-2, -4) *= Rational(-1, 2), Rational(-1, 1), sign::not_equal);
		add("(Rational(-2, -4) /= Rational(-1, 2)) == Rational(-1, 1)",
			Rational(-2, -4) /= Rational(-1, 2), Rational(-1, 1), sign::equal);
		add("(Rational(-2, -4) /= Rational(-1, 2)) != Rational(-5, 2)",
			Rational(-2, -4) /= Rational(-1, 2), Rational(-5, 2), sign::not_equal);
		return tests;
	}

	bool test_rational_case(const test_case &c) {
		Rational input = c.input;
		Rational expected = c.expected;
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

	test_result rational_tester() {
		const auto &tests = setup();
		size_t i = 0;
		size_t failed = 0;

		for (const auto &test_case : tests) {
			const bool &res = test_rational_case(test_case);
			if (!res) {
				++failed;
			}
			print_test(++i, test_case.name, res);
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
