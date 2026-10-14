#include "../include/mathlib/Complex.hpp"
#include "tests.hpp"
#include <cstddef>
#include <limits>

namespace {

	test_result complex_tester() {
		size_t i = 0;
		size_t failed = 0;
		failed += check("addition", Complex(1, 2) + Complex(1, 3), Complex(2, 5), ++i);
		failed += check("subtraction", Complex(3, 4) - Complex(1, 4), Complex(2, 0), ++i);
		failed +=
			check("multiplication", Complex(2, 3) * Complex(3, 4), Complex(-6, 17), ++i);
		failed += check("division", Complex(1, 2) / Complex(1, 4), Complex(Rational(9,17), Rational(-2,17)), ++i);
		failed +=
			check_throws("division by zero", []() { Complex(2, 1) / Complex(0, 0); }, ++i);
		failed += check_throws(
			"overflow",
			[]() { Complex(std::numeric_limits<int64_t>::max()) + Complex(1); }, ++i);
		failed += check_throws(
			"overflow",
			[]() { Complex(std::numeric_limits<int64_t>::max()) * Complex(2); }, ++i);
		failed += check_throws(
			"overflow",
			[]() { Complex(std::numeric_limits<int64_t>::min()) - Complex(1); }, ++i);
		failed += check_throws(
			"overflow",
			[]() { Complex(std::numeric_limits<int64_t>::min()) * Complex(-1, 2); }, ++i);
		failed += check_throws(
			"overflow", []() { -Complex(std::numeric_limits<int64_t>::min()); }, ++i);
		return {failed, i};
	}
} // namespace

test_result test_complex() {
	print_title("Complex");
	const auto &result = complex_tester();
	print_result(result);
	return result;
}
