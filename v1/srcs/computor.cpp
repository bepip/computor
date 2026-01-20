#include "../includes/computor.hpp"
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

Solution solve(const std::vector<double> &coeff) {
	printReducedForm(coeff);
	const uint8_t degree = coeff.size() - 1;

	switch (degree) {
	case 0:
		return solveDegreeZero(coeff);
	case 1:
		return solveDegreeOne(coeff);
	case 2:
		return solveDegreeTwo(coeff);
	default:
		throw std::logic_error(
			"The polynomial degee is strictly greater than 2, I can't solve.");
	}
}

double computeDelta(const std::vector<double> &coeff) {
	return coeff[1] * coeff[1] - 4 * coeff[2] * coeff[0];
}

void printReducedForm(const std::vector<double> &coeff) {
	assert(!coeff.empty());

	std::cout << "Reduced form: ";
	double first = coeff[0];
	if (first < 0)
		std::cout << "- ";
	std::cout << std::abs(first) << " * X^0";
	for (size_t i = 1; i < coeff.size(); ++i) {
		double a = coeff[i];
		std::cout << (a > 0 ? " + " : " - ") << std::abs(a) << " * X^" << i;
	}
	std::cout << " = 0" << std::endl;
}

Solution solveDegreeTwo(const std::vector<double> &coeff) {
	assert(coeff.size() == 3);
	const double delta = computeDelta(coeff);
	if (delta < 0) {
		double absDelta = std::abs(delta);
		double diviser = 2 * coeff[2];
		return {Solution::Type::DiscriminantNegative,
				{Complex(-coeff[1] / diviser, std::sqrt(absDelta) / diviser),
				 Complex(-coeff[1] / diviser, -std::sqrt(absDelta) / diviser)}};
	} else if (delta > 0) {
		Complex c((-coeff[1] + std::sqrt(delta)) / (2 * coeff[2]),
				  (-coeff[1] - std::sqrt(delta)) / (2 * coeff[2]));
		return {Solution::Type::DiscriminantPositive,
				{Complex((-coeff[1] + std::sqrt(delta)) / (2 * coeff[2]), 0),
				 Complex((-coeff[1] - std::sqrt(delta)) / (2 * coeff[2]), 0)}};
	} else {
		return {Solution::Type::DiscriminantZero,
				{Complex(-coeff[1] / (2 * coeff[2]), 0)}};
	}
}

Solution solveDegreeOne(const std::vector<double> &coeff) {
	assert(coeff.size() == 2);
	const double a = coeff[1];
	const double b = coeff[0];
	return {Solution::Type::OneSolution, {Complex(-b / a, 0)}};
}

Solution solveDegreeZero(const std::vector<double> &coeff) {
	assert(coeff.size() == 1);
	if (coeff[0] == 0) {
		return {Solution::Type::InfiniteSolutions, {}};
	}
	return {Solution::Type::NoSolution, {}};
}
