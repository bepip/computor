#include "../include/mathlib/Rational.hpp"
#include "tests.hpp"
#include <cstddef>
#include <cstdint>
#include <limits>
#include <string_view>

namespace {
	test_result rational_tester() {
		size_t i = 0;
		size_t failed = 0;

		failed += check("addition", Rational(1, 2) + Rational(1, 3), Rational(5, 6), ++i);
		failed +=
			check("subtraction", Rational(3, 4) - Rational(1, 4), Rational(1, 2), ++i);
		failed +=
			check("multiplication", Rational(2, 3) * Rational(3, 4), Rational(1, 2), ++i);
		failed += check("division", Rational(1, 2) / Rational(1, 4), Rational(2), ++i);
		failed += check("power", Rational(2) ^ Rational(3), Rational(8), ++i);
		failed += check("power 0^0", Rational(0) ^ Rational(0), Rational(1), ++i);
		failed += check("power 1^0", Rational(1) ^ Rational(0), Rational(1), ++i);
		failed +=
			check("power negative base", Rational(-2) ^ Rational(3), Rational(-8), ++i);
		failed +=
			check_throws("division by zero", []() { Rational(2) / Rational(0); }, ++i);
		failed += check_throws(
			"overflow",
			[]() { Rational(std::numeric_limits<int64_t>::max()) + Rational(1); }, ++i);
		failed += check_throws(
			"overflow",
			[]() { Rational(std::numeric_limits<int64_t>::max()) * Rational(2); }, ++i);
		failed += check_throws(
			"overflow",
			[]() { Rational(std::numeric_limits<int64_t>::min()) - Rational(1); }, ++i);
		failed += check_throws(
			"overflow",
			[]() { Rational(std::numeric_limits<int64_t>::min()) * Rational(-1); }, ++i);
		failed += check_throws(
			"overflow", []() { -Rational(std::numeric_limits<int64_t>::min()); }, ++i);

		return {failed, i};
	}
} // namespace

test_result test_rational() {
	print_title("Rationals");
	const auto &result = rational_tester();
	print_result(result);
	return result;
}
