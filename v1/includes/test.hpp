#pragma once

#include "Parser.hpp"
#include "computor.hpp"
#include <string>

struct TestCase {
	std::string name;
	std::string input;
	Solution expected;
};

void runTest(const TestCase &tc, Parser &parser);
void runTests();
