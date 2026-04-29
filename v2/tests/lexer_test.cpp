#include "../include/interpreter/Lexer.hpp"
#include "tests.hpp"
#include <cstddef>
#include <cstdio>
#include <string>
#include <vector>

namespace {
	struct token_test {
		std::string input;
		std::vector<Token> expected_tokens;
	};

	case_result test_tokenize_case(std::string_view input,
								   const std::vector<Token> &expected_tokens) {
		Lexer lexer(input);
		bool passed = true;
		auto tokens = lexer.tokenize();

		for (size_t i = 0; i < tokens.size() && i < expected_tokens.size(); ++i) {
			const auto &token = tokens[i];
			const auto &expected_t = expected_tokens[i];
			if (token != expected_t) {
				passed = false;
				return {false, i};
			}
		}
		return {passed, 0};
	}

	std::vector<token_test> setup_tokenize_test() {
		std::vector<token_test> tests;

		auto add_test_case = [&](std::string_view input, std::vector<Token> et) {
			tests.emplace_back(token_test{std::string(input), et});
		};
		add_test_case("5.5+-*/()6", {
										{token_type::Number, "5.5", 5.5},
										{token_type::Plus, "+", 0},
										{token_type::Minus, "-", 0},
										{token_type::Mul, "*", 0},
										{token_type::Div, "/", 0},
										{token_type::LParen, "(", 0},
										{token_type::RParen, ")", 0},
										{token_type::Number, "6", 6},
										{token_type::End, "", 0},
									});
		add_test_case("1 + 1 / 2.0", {
										 {token_type::Number, "1", 1},
										 {token_type::Plus, "+", 0},
										 {token_type::Number, "1", 1},
										 {token_type::Div, "/", 0},
										 {token_type::Number, "2.0", 2.0},
										 {token_type::End, "", 0},
									 });

		add_test_case("                   \t", {
												   {token_type::End, "", 0},
											   });

		add_test_case("A", {
							   {token_type::Invalid, "A", 0},
							   {token_type::End, "", 0},
						   });
		add_test_case("...", {
								 {token_type::Invalid, ".", 0},
								 {token_type::Invalid, ".", 0},
								 {token_type::Invalid, ".", 0},
								 {token_type::End, "", 0},
							 });
		return tests;
	}

	test_result test_tokenize() {
		const auto &tests = setup_tokenize_test();
		size_t i = 0;
		size_t failed = 0;
		for (const auto &[input, expected_tokens] : tests) {
			const case_result &cr = test_tokenize_case(input, expected_tokens);
			if (!cr.passed) {
				++failed;
			}
			print_test(++i, input, cr);
		}
		return {failed, tests.size()};
	}
} // namespace

// main function to call to run all lexer tests
void test_lexer() {
	print_title("Lexer");
	auto [failed, total] = test_tokenize();
	print_result(failed, total);
}
