#include "../includes/Parser.hpp"
#include "../includes/computor.hpp"
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <vector>

void test();

// TODO:
// - reading prompt when argc == 1
// - add testing cases with non-reduced inputs
int main(int argc, char *argv[]) {
	if (TEST == 1) {
		test();
		return 0;
	}
	if (argc > 2) {
		std::cout << "Expected 1 or 0 argument, got: " << argc << " arguments"
				  << std::endl;
		return 1;
	}
	if (argc == 2) {
		try {
			Parser parser;
			const std::vector<double> coeff = parser.parse(argv[1]);
			Solution solution = solve(coeff);
			display(coeff, solution);
		} catch (std::exception &e) {
			std::cout << "Unexpected Error :" << e.what() << std::endl;
		}
	} else {
		std::cout << "Case no input given\n";
	}
}

void test() {
	{
		std::cout << "===========================================";
		std::cout << std::endl;
		std::cout << GREEN << "Test degree 2, 2 solutions: " << NC;
		std::vector<double> coeff;
		coeff.push_back(4.0);
		coeff.push_back(4.0);
		coeff.push_back(0.5);
		const Complex expectedSolution1(-4 + 2 * std::sqrt(2), 0);
		const Complex expectedSolution2(-4 - 2 * std::sqrt(2), 0);

		Solution solution = solve(coeff);
		display(coeff, solution);
		assert(solution.type == Solution::Type::DiscriminantPositive);
		assert(solution.roots.size() == 2);
		assert(solution.roots[0].real == expectedSolution1.real);
		assert(solution.roots[0].imag == expectedSolution1.imag);
		assert(solution.roots[1].real == expectedSolution2.real);
		assert(solution.roots[1].imag == expectedSolution2.imag);
		std::cout << "✅" << std::endl;
	}
	{
		std::cout << "===========================================";
		std::cout << std::endl;
		std::cout << GREEN << "Test degree 2, 1 solution: " << NC;
		std::vector<double> coeff;
		coeff.push_back(4.0);
		coeff.push_back(4.0);
		coeff.push_back(1.0);
		const Complex expectedSolution(-2, 0);

		Solution solution = solve(coeff);
		display(coeff, solution);
		assert(solution.type == Solution::Type::DiscriminantZero);
		assert(solution.roots.size() == 1);
		assert(solution.roots[0].real == expectedSolution.real);
		assert(solution.roots[0].imag == expectedSolution.imag);
		std::cout << "✅" << std::endl;
	}
	{
		std::cout << "===========================================";
		std::cout << std::endl;
		std::cout << GREEN << "Test degree 2, 2 complex solutions: " << NC;
		std::vector<double> coeff;
		coeff.push_back(4.0);
		coeff.push_back(4.0);
		coeff.push_back(5.0);

		const Complex expectedSolution1(-2.0 / 5.0, 4.0 / 5.0);
		const Complex expectedSolution2(-2.0 / 5.0, -4.0 / 5.0);
		Solution solution = solve(coeff);
		display(coeff, solution);
		assert(solution.type == Solution::Type::DiscriminantNegative);
		assert(solution.roots.size() == 2);
		assert(solution.roots[0].real == expectedSolution1.real);
		assert(solution.roots[0].imag == expectedSolution1.imag);
		assert(solution.roots[1].real == expectedSolution2.real);
		assert(solution.roots[1].imag == expectedSolution2.imag);

		std::cout << "✅" << std::endl;
	}
	{
		std::cout << "===========================================";
		std::cout << std::endl;
		std::cout << GREEN << "Test degree 1, 1 solution: " << NC;
		std::vector<double> coeff;
		coeff.push_back(-1.0);
		coeff.push_back(2);
		const Complex expectedSolution(1 / 2.0, 0);

		Solution solution = solve(coeff);
		display(coeff, solution);
		assert(solution.type == Solution::Type::OneSolution);
		assert(solution.roots.size() == 1);
		assert(solution.roots[0].real == expectedSolution.real);
		assert(solution.roots[0].imag == expectedSolution.imag);
		std::cout << "✅" << std::endl;
	}
	{
		std::cout << "===========================================";
		std::cout << std::endl;
		std::cout << GREEN << "Test degree 0, 0 solution :" << NC;
		std::vector<double> coeff;
		coeff.push_back(2);

		Solution solution = solve(coeff);
		display(coeff, solution);
		assert(solution.type == Solution::Type::NoSolution);
		assert(solution.roots.empty());
		std::cout << "✅" << std::endl;
	}
	{
		std::cout << "===========================================";
		std::cout << std::endl;
		std::cout << GREEN << "Test degree 0, infinite: " << NC;
		std::vector<double> coeff;
		coeff.push_back(0.0);

		Solution solution = solve(coeff);
		display(coeff, solution);
		assert(solution.type == Solution::Type::InfiniteSolutions);
		assert(solution.roots.empty());
		std::cout << "✅" << std::endl;
		std::cout << "===========================================";
		std::cout << std::endl;
	}
}
