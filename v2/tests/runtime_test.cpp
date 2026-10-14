#include "tests.hpp"
#include <exception>
#include <string_view>

namespace {
	test_result runtime_tester() {

		size_t i = 0;
		size_t failed = 0;
		Runtime r;
		failed += check_expression(r, "1+1", Rational(2), ++i, "basic math");
		failed += check_expression(r, "2 + 3 * 4", Rational(14), ++i, "basic math");
		failed += check_expression(r, "(2 + 3) * 4", Rational(20), ++i, "basic math");
		failed += check_expression(r, "2 ^ 3", Rational(8), ++i, "basic math");
		failed += check_expression(r, "5 % 2", Rational(1), ++i, "basic math");
		failed += check_expression(r, "A=1+1", Rational(2), ++i, "saving variable");
		failed += check_expression(r, "A*6", Rational(12), ++i, "using saved variable");
		failed += check_expression(r, "a=A*6", Rational(12), ++i,
								   "changing value of a saved variable");
		failed += check_expression(r, "a", Rational(12), ++i,
								   "checking new value of saved variable");
		failed += check_expression(r, "abc = a+21 +69i", Complex(33, 69), ++i,
								   "Substituting a variable in a calculation");
		failed += check_expression(r, "A = a+21 +69i", Complex(33, 69), ++i,
								   "changing type of saved variable");
		failed +=
			check_expression(r, "A*i+ 2^2", Complex(-65, 33), ++i, "complex computation");
		failed += check_expression(r, "A-69i", Rational(33), ++i, "complex to rational");
		failed += check_expression(r, "[[1,1];[1,1]]", Matrix(2, 2, {1, 1, 1, 1}), ++i,
								   "Matrix printing");
		failed += check_expression(
			r, "[[1,1];[1,1]]**[[1,1];[1,1]]",
			Matrix(2, 2, {1, 1, 1, 1}).matrix_multiplication(Matrix(2, 2, {1, 1, 1, 1})),
			++i, "matrix multiplication");
		failed += check_expression_throws(r, "[[1,1,1];[1,1,1]]**[[1,1];[1,1]]", ++i,
										  "matrix multiplication on wrong dimensions");
		failed += check_expression_throws(r, "1+ [[1,1];[1,1]]", ++i,
										  "Adding a scalar to a matrix");
		failed += check_expression_throws(r, "1 / [[1,1];[1,1]]", ++i,
										  "dividing a scalar by a matrix");
		failed += check_expression_throws(r, "1 - [[1,1];[1,1]]", ++i,
										  "subtracting a scalar to a matrix");
		failed += check_expression(r, "2*[[1,1];[1,1]]", Matrix(2, 2, {2, 2, 2, 2}), ++i,
								   "multiplying a matrix by a scalar");
		failed += check_expression(r, "[[1,1];[1,1]]*2", Matrix(2, 2, {2, 2, 2, 2}), ++i,
								   "multiplying a matrix by a scalar");
		failed += check_expression_throws(r, "[[i,1];[1,1]]", ++i,
										  "matrices only accept Rational elements");
		failed += check_expression_throws(r, "B^2", ++i, "using a non defined var");
		// TODO: test =?; ?; eq solving
		std::cout << YELLOW << "Running f(x) = 2*x + 1" << NC << std::endl;
		try {
			r.execute("f(x) = 2*x + 1");
			failed += check_expression(r, "f(5)", Rational(11), ++i, "image calculation");
			failed += check_expression(r, "f(0)", Rational(1), ++i, "image calculation");
			failed +=
				check_expression(r, "f(10)", Rational(21), ++i, "image calculation");
			std::cout << YELLOW << "Running a = 10" << NC << std::endl;
			r.execute("a=10");
			std::cout << YELLOW << "Running f(x) = a + x" << NC << std::endl;
			r.execute("f(x) = a + x");
			failed += check_expression(r, "f(5)", Rational(15), ++i, "image calculation");
			r.execute("f(x) = x + 1");
			failed += check_expression(r, "f(5)", Rational(6), ++i, "Reassign function");

			r.execute("f(x) = x * 2");
			check_expression(r, "f(5)", Rational(10), ++i, "Reassign function");
			std::cout << YELLOW << "f(x) = x + 1" << NC << std::endl;
			r.execute("f(x) = x + 1");
			std::cout << YELLOW << "g(x) = 2*x" << NC << std::endl;
			r.execute("g(x) = 2*x");

			check_expression(r, "f(g(3))", Rational(7), ++i, "Function composition");
			/*
			 *5. Invalid function calls
			 *Test cases such as calling an undefined function or passing malformed
			 * arguments should verify that the interpreter reports an error rather than
			 * crashing.
			 * */
		} catch (std::exception &) {
			failed += 1;
		}
		return {failed, i};
	}
} // namespace

test_result test_runtime() {
	print_title("runtime");
	const auto &result = runtime_tester();
	print_result(result);
	return result;
}
