#include "dualSimplexSolver.h"

DualSimplexSolver::DualSimplexSolver(int n, int m, Matrix c, Matrix a, Matrix b, Matrix d, Matrix e):
	Solver(n, m, c, a, b, d, e) {}

DualSimplexSolver::~DualSimplexSolver() {}

void DualSimplexSolver::solve(int &k, double &y, Matrix &x) {
	// ...
}