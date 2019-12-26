#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "row.h"
using namespace std;

class Matrix {
public:
	Matrix();
	Matrix(int row, int column);
	Matrix(int row, int column, double constant);
	Matrix(int row, int column, double *data);
	Matrix(const Matrix &mat);
	~Matrix();

	Matrix getRow(int index);
	Matrix getColumn(int index);
	Matrix getRows(int beginIndex, int endIndex);
	Matrix getColumns(int beginIndex, int endIndex);

	Matrix operator+(const Matrix &mat) const;
	Matrix operator-(const Matrix &mat) const;
	Matrix operator*(double scale) const;
	friend Matrix operator*(double scale, const Matrix &mat);
	Matrix operator*(const Matrix &mat) const;

	Row operator[](int index);
	const Row operator[](int index) const;

	friend istream& operator>>(istream &is, const Matrix &mat);
	friend ostream& operator<<(ostream &os, const Matrix &mat);

private:
	int row;
	int column;
	double *data;
};

#endif