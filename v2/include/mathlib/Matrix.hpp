#pragma once

#include "Rational.hpp"
#include <cstddef>
#include <ostream>
#include <vector>

class Matrix {
  private:
	const size_t _rows;
	const size_t _columns;
	std::vector<Rational> _data;

  public:
	Matrix(size_t rows, size_t columns);
	Matrix(size_t rows, size_t columns, std::vector<Rational> data);

	Rational &at(size_t row, size_t col);
	const Rational &at(size_t row, size_t col) const;

	std::vector<Rational> &raw_data() const;
	size_t rows() const;
	size_t columns() const;

	Matrix operator+(const Matrix &rhs) const;
	Matrix operator-(const Matrix &rhs) const;
	Matrix operator*(const Matrix &rhs) const;			   // element-wise
	Matrix matrix_multiplication(const Matrix &rhs) const; // matrix multiplication
	Matrix operator*(const Rational &scalar) const;
};

std::ostream &operator<<(std::ostream &out, const Matrix &m);
