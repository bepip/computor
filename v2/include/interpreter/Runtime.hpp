#pragma once

#include <string>
#include <string_view>
#include <vector>

class Runtime {
  public:
	void execute(std::string_view line);

  private:
	std::vector<std::string> _history;
};
