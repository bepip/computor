#include "debug.hpp"
#include <iostream>
#include <string>

void debug(const std::string &msg) {
	if (DEBUG != 0) {
		std::cout << "DEBUG: " << msg << std::endl;
	}
}
