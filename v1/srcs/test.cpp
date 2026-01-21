#include "../includes/test.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

// NOTE: could improve test by sorting roots: right now {r1, r2} != {r2, r1}

void runTest(const TestCase &tc, Parser &parser) {
	std::cout << "===========================================";
	std::cout << std::endl;
	std::cout << GREEN << "Test: " << tc.name << NC << std::endl
			  << YELLOW << "Input: " << tc.input << NC << std::endl;
	const auto parsed = parser.parse(tc.input);
	const auto inputSol = solve(parsed);
	display(parsed, inputSol);

	assert(inputSol.type == tc.expected.type);
	assert(inputSol.roots.size() == tc.expected.roots.size());
	assert(inputSol.roots == tc.expected.roots);
	std::cout << GREEN << "PASSED ✅" << NC << std::endl;
}

void runTests() {
	Parser parser;
	std::vector<TestCase> tests = {
		{"degree 2, 2 solutions",
		 "0.5 * X^2 + 4 * X^1 + 4 * X^0 = 0 * X^0",
		 {Solution::Type::DiscriminantPositive,
		  {
			  Complex(-4 + 2 * std::sqrt(2.0)),
			  Complex(-4 - 2 * std::sqrt(2.0))
		  }
		 }
		},
		{"degree 2, 1 solution",
		 "1.0 * X^2 + 4 * X^1 + 4 * X^0 = 0 * X^0",
		 {Solution::Type::DiscriminantZero,
		  {
			  Complex(-2.0)
		  }
		 }
		},
		{"degree 2, 2 complex solutions",
		 "5.0 * X^2 + 4 * X^1 + 4 * X^0 = 0 * X^0",
		 {Solution::Type::DiscriminantNegative,
		  {
			  Complex(-2.0 / 5.0, 4.0 / 5.0),
			  Complex(-2.0 / 5.0, -4.0 / 5.0)
		  }
		 }
		},
		{"degree 1, 1 solution",
		 "2 * X^1 - 1 * X^0 = 0 * X^0",
		 {Solution::Type::OneSolution,
		  {
			  Complex(1.0 / 2.0)
		  }
		 }
		},
		{"degree 0, no solution",
		 "- 2 * X^0 = 0 * X^0",
		 {Solution::Type::NoSolution,
		  {}
		 }
		},
		{"degree 0, infinite solutions",
		 "- 2 * X^0 = - 2 * X^0",
		 {Solution::Type::InfiniteSolutions,
		  {}
		 }
		},
		{"degree 3, can't solve",
		 "- 2 * X^0 = - 2 * X^0 + 9.33 * X^3",
		 {Solution::Type::DegreeTooHigh,
		  {}
		 }
		},
		{"degree 2, 2 solutions",
		 "- 2 * X^0 + 9.33 * X^3 - 19 * X^2 = 10 * X^2 - 3 * X^1 - 2 * X^0 + 9.33 * X^3",
		 {Solution::Type::DiscriminantPositive,
		  {
			  Complex(0),
			  Complex(3.0 / 29),
		  }
		 }
		},
		{"degree 0, infinite solutions",
		 "1 * X^0 - 2 * X^0 + 9.33 * X^3 - 19 * X^2 = 10 * X^2 - 3 * X^1 - 2 * X^0 + 9.33 * X^3 - 29 * X^2 + 3 * X^1 + 1 * X^0",
		 {Solution::Type::InfiniteSolutions,
		  {
		  }
		 }
		},
		{"degree 1, 1 solution",
		 "9.33 * X^3 - 19 * X^2 + 5 * X^1 = 10 * X^2 - 3 * X^1 - 2 * X^0 + 9.33 * X^3 - 29 * X^2 + 3 * X^1 + 1 * X^0",
		 {Solution::Type::OneSolution,
		  {
			  Complex(-1.0 / 5)
		  }
		 }
		},
		{"degree 2, 2 complex solutions",
		 "10 * X^2 + 9.33 * X^3 - 19 * X^2 + 5 * X^1 = 10 * X^2 - 3 * X^1 - 2 * X^0 + 9.33 * X^3 - 29 * X^2 + 3 * X^1 + 1 * X^0",
		 {Solution::Type::DiscriminantNegative,
		  {
			  Complex(-1.0 / 4, sqrt(15.0) / 20.0),
			  Complex(-1.0 / 4, - sqrt(15.0) / 20.0)
		  }
		 }
		},
	};
	for (const auto& tc: tests){
		runTest(tc, parser);
	}
	std::cout << "===========================================";
	std::cout << std::endl;
}
