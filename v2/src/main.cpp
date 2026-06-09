#include "../include/cli/Repl.hpp"
#include <stdio.h>
#include <string>
#include <vector>

int main(int ac, char *av[]) {
	if (ac == 1) {
		Repl repl;
		repl.run();
	} else {
		std::vector<std::string> v(av, av + ac);
		printf("Too many arguments %lu\n", v.size());
		return 1;
	}

	return 0;
}
