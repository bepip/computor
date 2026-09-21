#include "../../include/mathlib/Matrix.hpp"
#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

Matrix::Matrix(size_t rows, size_t columns) :
	Matrix(rows, columns, std::vector<Rational>(rows * columns, Rational())) {}

Matrix::Matrix(size_t rows, size_t columns, std::vector<Rational> data) :
	_rows(rows),
	_columns(columns),
	_data(data) {
	if (_rows * _columns != _data.size()) {
		throw std::invalid_argument("matrix size does not match data size");
	}
}

const Rational &Matrix::at(size_t row, size_t col) const {
	return _data[_columns * row + col];
}

Rational &Matrix::at(size_t row, size_t col) {
	return _data[_columns * row + col];
}

size_t Matrix::rows() const {
	return _rows;
}

size_t Matrix::columns() const {
	return _columns;
}

Matrix Matrix::operator+(const Matrix &rhs) const {
	if (_rows != rhs.rows() || _columns != rhs.columns()) {
		throw std::invalid_argument("Matrix: can't add two matrices of different sizes.");
	}
	std::vector<Rational> result_data(_data.size());

	for (size_t i(0); i < _data.size(); ++i) {
		result_data[i] = _data[i] + rhs._data[i];
	}
	return {_rows, _columns, result_data};
}

Matrix Matrix::operator-(const Matrix &rhs) const {
	if (_rows != rhs.rows() || _columns != rhs.columns()) {
		throw std::invalid_argument(
			"Matrix: can't substract two matrices of different sizes.");
	}
	std::vector<Rational> result_data(_data.size());

	for (size_t i(0); i < _data.size(); ++i) {
		result_data[i] = _data[i] - rhs._data[i];
	}
	return {_rows, _columns, result_data};
}

Matrix Matrix::operator*(const Matrix &rhs) const {
	if (_rows != rhs.rows() || _columns != rhs.columns()) {
		throw std::invalid_argument(
			"Matrix: can't multiply element wise two matrices of different sizes.");
	}
	std::vector<Rational> result_data(_data.size());

	for (size_t i(0); i < _data.size(); ++i) {
		result_data[i] = _data[i] * rhs._data[i];
	}
	return {_rows, _columns, result_data};
}

Matrix Matrix::operator*(const Rational &scalar) const {
	std::vector<Rational> result_data(_data.size());

	for (size_t i(0); i < _data.size(); ++i) {
		result_data[i] = scalar * _data[i];
	}
	return {_rows, _columns, result_data};
}

Matrix Matrix::matrix_multiplication(const Matrix &rhs) const {
	if (_columns != rhs.rows()) {
		throw std::invalid_argument("Matrix: invalid matrices sizes");
	}
	size_t res_rows = _rows;
	size_t res_cols = rhs.columns();
	Matrix res(res_rows, res_cols);
	std::vector<Rational> res_data(res_rows * res_cols);

	for (size_t i = 0; i < res_rows; ++i) {
		for (size_t j = 0; j < res_cols; ++j) {
			for (size_t k = 0; k < _columns; ++k) {
				res.at(i, j) += at(i, k) * rhs.at(k, j);
			}
		}
	}
	return res;
}

std::ostream &operator<<(std::ostream &out, const Matrix &m) {
	for (size_t i(0); i < m.rows(); ++i) {
		out << "[ ";
		for (size_t j(0); j < m.columns(); ++j) {
			out << m.at(i, j);
			if (j != m.columns() - 1) {
				out << ", ";
			}
		}
		out << " ]\n";
	}
	return out;
}
