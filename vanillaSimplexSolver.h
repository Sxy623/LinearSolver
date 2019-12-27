#ifndef VANILLA_SIMPLEX_SOLVER_H
#define VANILLA_SIMPLEX_SOLVER_H

#include "solver.h"

class VanillaSimplexSolver: public Solver {
public:
	VanillaSimplexSolver(int n, int m, Matrix c, Matrix a, Matrix b, Matrix d, Matrix e);
	~VanillaSimplexSolver();

	virtual void solve();
};

#endif