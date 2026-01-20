#pragma once

#include "Complex.hpp"
#include <vector>

// Text colors
#define RED "\e[31m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define BLUE "\e[34m"
#define MAGENTA "\e[35m"
#define CYAN "\e[36m"
#define WHITE "\e[37m"
#define NC "\033[0m"

#ifndef TEST
#define TEST 0
#endif // !TEST

struct Solution {
	enum class Type {
		NoSolution,
		DiscriminantNegative,
		DiscriminantZero,
		DiscriminantPositive,
		InfiniteSolutions,
		OneSolution,
		DegreeTooHigh
	};
	Type type;
	std::vector<Complex> roots;
};

Solution solve(const std::vector<double> &coefs);

void display(const std::vector<double> &coeff, const Solution &solution);
