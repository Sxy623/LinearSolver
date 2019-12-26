#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
using namespace std;

class Matrix {
public:
	Matrix();
	Matrix(int row, int column);
	Matrix(int row, int column, double constant);
	Matrix(int row, int column, double *data);
	Matrix(const Matrix &mat);

	Matrix getRow(int index);
	Matrix getColumn(int index);
	Matrix getRows(int beginIndex, int endIndex);
	Matrix getColumns(int beginIndex, int endIndex);

	~Matrix();

	friend istream& operator>>(istream &is, Matrix &mat);
	friend ostream& operator<<(ostream &os, Matrix &mat);

private:
	int row;
	int column;
	double *data;
};

#endif