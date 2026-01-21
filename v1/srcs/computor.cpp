#include "../includes/computor.hpp"
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <vector>

namespace {
	Solution solveDegreeTwo(const std::vector<double> &coeff) {
		const double a = coeff[2];
		const double b = coeff[1];
		const double c = coeff[0];
		const double delta = b * b - 4 * a * c;

		if (delta < -constants::eps) {
			const double sqrtAbs = std::sqrt(-delta);
			return {Solution::Type::DiscriminantNegative,
					{Complex(-b / (2 * a), sqrtAbs / (2 * a)),
					 Complex(-b / (2 * a), -sqrtAbs / (2 * a))}};
		} else if (delta > constants::eps) {
			const double sqrtDelta = std::sqrt(delta);
			return {Solution::Type::DiscriminantPositive,
					{Complex((-b + sqrtDelta) / (2 * a)),
					 Complex((-b - sqrtDelta) / (2 * a))}};
		} else {
			return {Solution::Type::DiscriminantZero, {Complex(-b / (2 * a))}};
		}
	}

	Solution solveDegreeOne(const std::vector<double> &coeff) {
		const double a = coeff[1];
		const double b = coeff[0];
		return {Solution::Type::OneSolution, {Complex(-b / a)}};
	}

	Solution solveDegreeZero(const std::vector<double> &coeff) {
		return isZero(coeff[0]) ? Solution{Solution::Type::InfiniteSolutions, {}}
								: Solution{Solution::Type::NoSolution, {}};
	}
} // namespace

Solution solve(const std::vector<double> &coeff) {
	if (coeff.empty())
		return {Solution::Type::InfiniteSolutions, {}};
	const size_t degree = coeff.size() - 1;

	switch (degree) {
		case 0:
			return solveDegreeZero(coeff);
		case 1:
			return solveDegreeOne(coeff);
		case 2:
			return solveDegreeTwo(coeff);
		default:
			return {Solution::Type::DegreeTooHigh, {}};
	}
}

bool isZero(double x) {
	return std::abs(x) < constants::eps;
}

double normalizeZero(double x) {
	return (std::abs(x) < constants::eps) ? 0.0 : x;
}
