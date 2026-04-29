
#pragma once

#include <string_view>

// Text colors
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define NC "\033[0m"

struct test_result {
	size_t failed;
	size_t total;
};

struct case_result {
	bool passed;
	size_t fail_index;
};

void test_lexer();

void print_title(std::string_view title);
void print_test(size_t count, std::string_view msg, const case_result& cr);
void print_result(size_t failed, size_t total);
