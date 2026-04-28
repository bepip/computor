#include "../../include/common/utils.hpp"
#include <algorithm>
#include <string>

std::string str::to_lower(std::string_view sv) {
	std::string str(sv);
	std::transform(str.begin(), str.end(), str.begin(),
				   [](unsigned char c) { return std::tolower(c); });
	return str;
}

std::string str::to_upper(std::string_view sv) {
	std::string str(sv);
	std::transform(str.begin(), str.end(), str.begin(),
				   [](unsigned char c) { return std::toupper(c); });
	return str;
}
