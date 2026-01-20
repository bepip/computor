#include "../includes/computor.hpp"
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sys/types.h>
#include <vector>

namespace {
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
} // namespace

void display(const std::vector<double> &coeff, const Solution &solution) {
	const uint degree = coeff.size() - 1;
	printReducedForm(coeff);
	switch (solution.type) {
		case Solution::Type::InfiniteSolutions:
			assert(degree == 0);
			std::cout << "Any real number is a solution" << std::endl;
			break;
		case Solution::Type::NoSolution:
			assert(degree == 0);
			std::cout << "No solution." << std::endl;
			break;
		case Solution::Type::OneSolution:
			assert(degree == 1);
			std::cout << "Polynomial degree: " << degree << std::endl;
			std::cout << "The solution is:" << std::endl
					  << solution.roots[0].real() << std::endl;
			break;
		case Solution::Type::DiscriminantNegative:
			{
				assert(degree == 2);
				std::cout << "Polynomial degree: " << degree << std::endl;
				std::cout
					<< "Discriminant is strictly negative, the two complex solutions are:"
					<< std::endl;
				double real = solution.roots[0].real();
				double imag = solution.roots[0].imag();
				std::cout << real << (imag > 0 ? " + " : " - ") << std::abs(imag) << "i"
						  << std::endl;
				real = solution.roots[1].real();
				imag = solution.roots[1].imag();
				std::cout << real << (imag > 0 ? " + " : " - ") << std::abs(imag) << "i"
						  << std::endl;
				break;
			}
		case Solution::Type::DiscriminantZero:
			assert(degree == 2);
			std::cout << "Polynomial degree: " << degree << std::endl;
			std::cout << "Discriminant is zero, the solution is:" << std::endl
					  << solution.roots[0].real() << std::endl;
			break;
		case Solution::Type::DiscriminantPositive:
			assert(degree == 2);
			std::cout << "Polynomial degree: " << degree << std::endl;
			std::cout << "Discriminant is strictly positive, the two solutions are:"
					  << std::endl
					  << solution.roots[0].real() << std::endl
					  << solution.roots[1].real() << std::endl;
			break;
		case Solution::Type::DegreeTooHigh:
			assert(degree > 2);
			std::cout << "Polynomial degree: " << degree << std::endl;
			std::cout
				<< "The polynomial degree is strictly greater than 2, I can't solve."
				<< std::endl;
			break;
	}
}
