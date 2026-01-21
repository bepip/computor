#include "../includes/computor.hpp"
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <sys/types.h>
#include <vector>

namespace {
	void printReducedForm(const std::vector<double> &coeff) {
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
} // namespace

void display(const std::vector<double> &coeff, const Solution &solution) {
	const size_t degree = coeff.empty() ? 0 : coeff.size() - 1;
	std::cout << "Polynomial degree: " << degree << std::endl;
	if (degree < 3)
		printReducedForm(coeff);
	switch (solution.type) {
		case Solution::Type::InfiniteSolutions:
			std::cout << "Any real number is a solution" << std::endl;
			break;
		case Solution::Type::NoSolution:
			std::cout << "No solution." << std::endl;
			break;
		case Solution::Type::OneSolution:
			std::cout << "The solution is:" << std::endl;
			std::cout << solution.roots[0] << std::endl;
			break;
		case Solution::Type::DiscriminantNegative:
			{
				std::cout
					<< "Discriminant is strictly negative, the two complex solutions are:"
					<< std::endl;
				std::cout << solution.roots[0] << std::endl;
				std::cout << solution.roots[1] << std::endl;
				break;
			}
		case Solution::Type::DiscriminantZero:
			std::cout << "Discriminant is zero, the solution is:" << std::endl
					  << solution.roots[0] << std::endl;
			break;
		case Solution::Type::DiscriminantPositive:
			std::cout << "Discriminant is strictly positive, the two solutions are:"
					  << std::endl
					  << solution.roots[0] << std::endl
					  << solution.roots[1] << std::endl;
			break;
		case Solution::Type::DegreeTooHigh:
			std::cout
				<< "The polynomial degree is strictly greater than 2, I can't solve."
				<< std::endl;
			break;
	}
}
