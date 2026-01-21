#pragma once

#include "Complex.hpp"
#include <vector>

// Text colors
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define NC "\033[0m"

#ifndef TEST
#define TEST 0
#endif // !TEST

namespace constants {
	inline constexpr double eps = 1e-9;
}

struct Complex;

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

	bool operator==(const Solution &other) const {
		return type == other.type && roots == other.roots;
	}
};

Solution solve(const std::vector<double> &coeff);

void display(const std::vector<double> &coeff, const Solution &solution);
bool isZero(double x);
double normalizeZero(double x);
