#ifndef DUAL_SIMPLEX_SOLVER_H
#define DUAL_SIMPLEX_SOLVER_H

#include "solver.h"

class DualSimplexSolver: public Solver {
public:
	DualSimplexSolver(int n, int m, Matrix c, Matrix a, Matrix b, Matrix d, Matrix e);
	~DualSimplexSolver();

	virtual void solve(int &k, double &y, Matrix &x);
};

#endif