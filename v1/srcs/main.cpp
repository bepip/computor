#include "../includes/Parser.hpp"
#include "../includes/computor.hpp"
#include "../includes/test.hpp"
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
	if (TEST == 1) {
		runTests();
		return 0;
	}
	if (argc > 2) {
		std::cerr << "Expected 1 or 0 argument, got: " << argc << " arguments"
				  << std::endl;
		return 1;
	}
	std::string input = "";
	if (argc == 1) {
		std::cout << "Please enter the equation: ";
		std::getline(std::cin, input);
	} else {
		input = std::string(argv[1]);
	}
	if (input.empty()) {
		std::cerr << "Error\n";
		exit(1);
	}
	try {
		Parser parser;
		const std::vector<double> coeff = parser.parse(input);
		Solution solution = solve(coeff);
		display(coeff, solution);
	} catch (std::exception &e) {
		std::cout << "Unexpected Error :" << e.what() << std::endl;
	}
}
