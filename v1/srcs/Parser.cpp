#include "../includes/Parser.hpp"
#include "../includes/computor.hpp"
#include <bits/types/cookie_io_functions_t.h>
#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <vector>

namespace {
	void parseSide(const std::string &side, std::map<int, double> &poly, int sign) {
		std::istringstream iss(side);
		std::string token;

		double currentSign = 1.0;

		while (iss >> token) {
			if (token == "+") {
				currentSign = 1.0;
			} else if (token == "-") {
				currentSign = -1.0;
			} else {
				double coeff = std::stod(token);
				iss >> token;
				iss >> token;
				int power = std::stoi(token.substr(2));
				poly[power] += sign * currentSign * coeff;
			}
		}
	}

	void trimTrailingZeros(std::vector<double> &coeff) {
		while (!coeff.empty() && isZero(coeff.back() && coeff.begin() != coeff.end())) {
			coeff.pop_back();
		}
	}

} // namespace

Parser::Parser() {}

std::vector<double> Parser::parse(const std::string &input) {
	if (input.empty()) {
		std::cerr << "Error\n";
		exit(1);
	}
	size_t eqPos = input.find('=');
	if (eqPos == std::string::npos)
		throw std::runtime_error("Invalid equation");
	std::string lhs = input.substr(0, eqPos);
	std::string rhs = input.substr(eqPos + 1);

	std::map<int, double> poly;
	parseSide(lhs, poly, +1);
	parseSide(rhs, poly, -1);

	if (poly.empty()) {
		return {};
	}

	int maxPower = poly.rbegin()->first;
	std::vector<double> coeff(maxPower + 1, 0.0);

	for (const auto &[power, value] : poly) {
		coeff[power] = value;
	}
	trimTrailingZeros(coeff);
	return coeff;
}
