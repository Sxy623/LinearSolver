#ifndef SOLVER_H
#define SOLVER_H

#include "matrix.h"
#include "utility.h"
#include <vector>
using namespace std;

class Solver {
public:
	Solver(int n, int m, Matrix c, Matrix a, Matrix b, Matrix d, Matrix e);
	~Solver();

	void relax();
	void normalize();
	virtual void solve(int &k, double &y, Matrix &x) = 0;
#ifdef DEBUG
	void print();
#endif

protected:
	int n, m;
	Matrix c;
	Matrix a, b, d;
	Matrix e;
	vector<int> negative;  // xi -> -xi, if xi <= 0
	vector<pair<int, int> > noConstraints;  // xi -> xi - xj, if no constraints on xi
};

#endif