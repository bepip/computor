#include "../include/mathlib/Matrix.hpp"
#include "tests.hpp"
#include <cstddef>
#include <iostream>

namespace {

	test_result complex_tester() {
		size_t i = 0;
		size_t failed = 0;
		{
			Matrix A(2, 2, {1, 2, 3, 4});
			Matrix B(2, 2, {1, 2, 3, 4});
			Matrix C(2, 2, {2, 4, 6, 8});
			failed += check("addition", A + B, C, ++i);
		}
		{
			Matrix A(2, 2, {1, 2, 3, 4});
			Matrix B(2, 2, {1, 2, 3, 4});
			Matrix C(2, 2, {0, 0, 0, 0});
			failed += check("subtraction", A - B, C, ++i);
		}
		{
			Matrix A(2, 2, {1, 2, 3, 4});
			Matrix B(2, 2, {1, 2, 3, 4});
			Matrix C(2, 2, {1, 4, 9, 16});
			failed += check("term mutliplication", A * B, C, ++i);
		}
		{
			Matrix A(2, 2, {1, 2, 3, 4});
			Matrix B(2, 2, {1, 2, 3, 4});
			Matrix C(2, 2, {7, 10, 15, 22});
			failed += check("matrix mutliplication", A.matrix_multiplication(B), C, ++i);
		}
		{
			Matrix A(2, 3, {1, 1, 1, 1, 1, 1});
			Matrix B(3, 2, {2, 2, 2, 2, 2, 2});
			Matrix C(2, 2, {6, 6, 6, 6});
			failed += check("matrix mutliplication", A.matrix_multiplication(B), C, ++i);
		}
		{
			Rational A(2);
			Matrix B(2, 2, {1, 2, 3, 4});
			Matrix C(2, 2, {2, 4, 6, 8});
			failed += check("scalar multiplication", B * A, C, ++i);
		}
		{
			Matrix A(2, 2, {1, 2, 3, 4});
			Matrix B(3, 2, {1, 2, 3, 4, 5, 6});
			failed += check_throws("Wrong dimension addition", [&]() { A + B; }, ++i);
		}
		{
			Matrix A(2, 2, {1, 2, 3, 4});
			Matrix B(3, 2, {1, 2, 3, 4, 5, 6});
			failed += check_throws("Wrong dimension subtraction", [&]() { A - B; }, ++i);
		}
		{
			Matrix A(2, 2, {1, 2, 3, 4});
			Matrix B(3, 2, {1, 2, 3, 4, 5, 6});
			failed +=
				check_throws("Wrong dimension term multiplication", [&]() { A *B; }, ++i);
		}
		{
			Matrix A(2, 2, {1, 2, 3, 4});
			Matrix B(3, 2, {1, 2, 3, 4, 5, 6});
			failed += check_throws(
				"Wrong dimension matrix multiplication",
				[&]() { A.matrix_multiplication(B); }, ++i);
		}
		return {failed, i};
	}
} // namespace

test_result test_matrix() {
	print_title("Matrix");
	const auto &result = complex_tester();
	print_result(result);
	return result;
}
