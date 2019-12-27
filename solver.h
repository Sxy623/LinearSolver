#ifndef SOLVER_H
#define SOLVER_H

#include "matrix.h"

class Solver {
public:
	Solver(int n, int m, Matrix c, Matrix a, Matrix b, Matrix d, Matrix e);
	~Solver();

	void relax();
	virtual void solve() = 0;

private:
	int n, m;
	Matrix c;
	Matrix a, b, d;
	Matrix e;
};

#endif