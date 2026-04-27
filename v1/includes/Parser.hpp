#pragma once

#include <string>
#include <vector>

// Parser object validates input
// throws on invalid input
// returns an array
class Parser {
  public:
	static std::vector<double> parse(const std::string &input);
};
