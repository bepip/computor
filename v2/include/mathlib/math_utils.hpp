#pragma once

namespace math {
	namespace constants {
		inline constexpr double eps = 1e-9;
	}

	bool is_zero(double x);
	double normalize_zero(double x);
	bool near_equal(double a, double b, double eps = constants::eps);
	double abs(double d);
} // namespace math
