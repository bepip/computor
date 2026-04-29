#pragma once

#include <algorithm>
#include <iterator>
#include <string_view>

template <typename Container, typename T>
bool contains(const Container &cont, const T &value) {
	return std::find(std::begin(cont), std::end(cont), value) != std::end(cont);
}

namespace str {
	std::string to_lower(std::string_view sv);
	std::string to_upper(std::string_view sv);
} // namespace str
