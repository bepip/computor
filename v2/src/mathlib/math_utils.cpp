#include "../../include/mathlib/math_utils.hpp"
#include <cmath>

namespace math {

	bool is_zero(double x) {
		return std::abs(x) < math::constants::eps;
	}

	double normalize_zero(double x) {
		return (std::abs(x) < math::constants::eps) ? 0.0 : x;
	}

	bool near_equal(double a, double b, double eps) {
		return std::abs(a - b) < eps;
	}
}; // namespace math
