#pragma once

#include "../../include/mathlib/Value.hpp"
#include <string>
#include <string_view>
#include <vector>

class Runtime {
  public:
	Value execute(std::string_view line);

  private:
	std::vector<std::string> _history;
};
