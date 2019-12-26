#include "matrix.h"

Matrix::Matrix() {
	row = 0;
	column = 0;
	data = NULL;
}

Matrix::Matrix(int row, int column): row(row), column(column) {
	data = new double[row * column];
	for(int i = 0; i < row * column; i++)
		data[i] = 0;
}

Matrix::Matrix(int row, int column, double constant): row(row), column(column) {
	data = new double[row * column];
	for(int i = 0; i < row * column; i++)
		data[i] = constant;
}

Matrix::Matrix(int row, int column, double *data): row(row), column(column) {
	this->data = new double[row * column];
	for(int i = 0; i < row * column; i++)
		this->data[i] = data[i];
}

Matrix::Matrix(const Matrix &mat) {
	row = mat.row;
	column = mat.column;
	data = new double[row * column];
	for(int i = 0; i < row * column; i++)
		data[i] = mat.data[i];
}

Matrix Matrix::getRow(int index) {
	Matrix result(1, column);
	for (int j = 0; j < column; j++)
		result.data[j] = data[index * column + j];
	return result;
}

Matrix Matrix::getColumn(int index) {
	Matrix result(row, 1);
	for (int i = 0; i < row; i++)
		result.data[i] = data[i * column + index];
	return result;
}

Matrix Matrix::getRows(int beginIndex, int endIndex) {
	Matrix result(endIndex - beginIndex, column);
	int count = 0;
	for (int i = beginIndex; i < endIndex; i++)
		for (int j = 0; j < column; j++)
			result.data[count++] = data[i * column + j];
	return result;
}

Matrix Matrix::getColumns(int beginIndex, int endIndex) {
	Matrix result(row, endIndex - beginIndex);
	int count = 0;
	for (int i = 0; i < row; i++)
		for (int j = beginIndex; j < endIndex; j++)
			result.data[count++] = data[i * column + j];
	return result;
}

Matrix::~Matrix() {
	if (data != NULL) {
		delete[] data;
		data = NULL;
	}
}

istream& operator>>(istream &is, Matrix &mat) {
	int row = mat.row;
	int column = mat.column;
	for(int i = 0; i < row * column; i++)
		is >> mat.data[i];
	return is;
}

ostream& operator<<(ostream &os, Matrix &mat) {
	int row = mat.row;
	int column = mat.column;
	for(int i = 0; i < row * column; i++)
		os << mat.data[i] << " \n"[i % column == column - 1];
	return os;
}