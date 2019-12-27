#include "vanillaSimplexSolver.h"

VanillaSimplexSolver::VanillaSimplexSolver(int n, int m, Matrix c, Matrix a, Matrix b, Matrix d, Matrix e):
	Solver(n, m, c, a, b, d, e) {}

VanillaSimplexSolver::~VanillaSimplexSolver() {}

void VanillaSimplexSolver::solve(int &k, double &y, Matrix &x) {
	// ...
}