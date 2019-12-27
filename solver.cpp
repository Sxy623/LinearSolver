#include "solver.h"
#include "utility.h"

Solver::Solver(int n, int m, Matrix c, Matrix a, Matrix b, Matrix d, Matrix e): 
	n(n), m(m), c(c), a(a), b(b), d(d), e(e) {}

Solver::~Solver() {}

void Solver::relax() {
	for (int i = 0; i < m; i++) {
		if (equal(d[i][0], 0)) continue;
		if (equal(d[i][0], 1)) {
			// ...
			continue;
		}
		if (equal(d[i][0], -1)) {
			// ...
			continue;
		}
	}
}