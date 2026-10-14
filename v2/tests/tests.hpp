#pragma once

#include "../include/interpreter/Runtime.hpp"
#include <exception>
#include <iostream>
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
#define REDCROSS RED "❌\033[0m"

struct test_result {
	size_t failed;
	size_t total;

	test_result &operator+=(const test_result &rhs) {
		failed += rhs.failed;
		total += rhs.total;
		return *this;
	}
};

struct case_result {
	bool passed;
	size_t fail_index;
};

// TODO: add all math tests in a single function
test_result test_lexer();
test_result test_rational();
test_result test_complex();
test_result test_matrix();
test_result test_runtime();

void clear_screen();
void print_title(std::string_view title);
void print_test(size_t count, std::string_view msg, const case_result &cr);
void print_test(size_t count, std::string_view msg, bool passed);
void print_result(test_result result);
int print_final_result(test_result result);

template <typename Function>
int check_throws(std::string_view name, Function operation, size_t count) {
	try {
		operation();
		print_test(count, name, false);
		return 1;
	} catch (const std::exception &e) {
		print_test(count, name, true);
		std::cout << "output: " << e.what() << std::endl;
		return 0;
	}
}

template <typename T>
int check(std::string_view name, const T &actual, const T &expected, size_t count) {
	int res = actual == expected;
	print_test(count, name, actual == expected);
	return !res;
}

template <typename T>
int check_expression(Runtime &runtime, std::string_view input, const T &expected,
					 size_t count, std::string_view name = "") {
	try {
		const Value result = runtime.execute(input);
		if (result.is<T>() && result.get<T>() == expected) {
			print_test(count, name, true);
			std::cout << "input: " << input << "\noutput:\n";
			result.println();
			return 0;
		} else {
			print_test(count, name, false);
			std::cout << "input: " << input << "\n";
			std::cout << "expected " << expected << " got ";
			result.println();

			return 1;
		}

	} catch (const std::exception &e) {
		print_test(count, name, false);
		std::cout << "input: " << input << "\n";
		std::cout << "output: " << e.what() << std::endl;
		return 1;
	}
}

int check_expression_throws(Runtime &runtime, std::string_view input, size_t count,
							std::string_view name = "");
