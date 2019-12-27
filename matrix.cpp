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

Matrix::~Matrix() {
	if (data != NULL) {
		delete[] data;
		data = NULL;
	}
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

void Matrix::appendRow(Matrix &mat) {

}

void Matrix::appendColumn(Matrix &mat) {

}

Matrix Matrix::operator+(const Matrix &mat) const {
	if (row != mat.row || column != mat.column) {
		cerr << "Error!" << endl;
		exit(0);
	}
	Matrix result(row, column);
	for(int i = 0; i < row * column; i++)
		result.data[i] = data[i] + mat.data[i];
	return result;
}

Matrix Matrix::operator-(const Matrix &mat) const {
	if (row != mat.row || column != mat.column) {
		cerr << "Error!" << endl;
		exit(0);
	}
	Matrix result(row, column);
	for(int i = 0; i < row * column; i++)
		result.data[i] = data[i] - mat.data[i];
	return result;
}

Matrix Matrix::operator*(double scale) const {
	Matrix result(row, column);
	for(int i = 0; i < row * column; i++)
		result.data[i] = scale * data[i];
	return result;
}

Matrix operator*(double scale, const Matrix &mat) {
	int row = mat.row;
	int column = mat.column;
	Matrix result(row, column);
	for(int i = 0; i < row * column; i++)
		result.data[i] = scale * mat.data[i];
	return result;
}

Matrix Matrix::operator*(const Matrix &mat) const {
	if (column != mat.row) {
		cerr << "Error!" << endl;
		exit(0);
	}
	Matrix result(row, mat.column);
	for (int i = 0; i < row; i++)
		for (int j = 0; j < mat.column; j++)
			for (int k = 0; k < column; k++)
				result.data[i * row + j] += data[i * row + k] * mat.data[k * row + j];
	return result;	
}

Row Matrix::operator[](int index) {
	if (index < 0 || index >= row) {
		cerr << "Index out of range: " << index << endl;
		exit(0);
	}
	return Row(column, data + index * column);
}

const Row Matrix::operator[](int index) const {
	if (index < 0 || index >= row) {
		cerr << "Index out of range: " << index << endl;
		exit(0);
	}
	return Row(column, data + index * column);
}

istream& operator>>(istream &is, const Matrix &mat) {
	int row = mat.row;
	int column = mat.column;
	for(int i = 0; i < row * column; i++)
		is >> mat.data[i];
	return is;
}

ostream& operator<<(ostream &os, const Matrix &mat) {
	int row = mat.row;
	int column = mat.column;
	for(int i = 0; i < row * column; i++)
		os << mat.data[i] << " \n"[i % column == column - 1];
	return os;
}