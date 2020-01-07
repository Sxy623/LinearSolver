#ifndef DUAL_SIMPLEX_SOLVER_H
#define DUAL_SIMPLEX_SOLVER_H

#include "solver.h"
#include <vector>
#include <cmath>

#define MAX = 1e9
#define GRE(x, y) (x > y && !equal(x, y))
#define GEQ(x, y) (x > y || equal(x, y))


class DualSimplexSolver : public Solver {
public:
    DualSimplexSolver(int n, int m, const Matrix& c, const Matrix& a, const Matrix& b, const Matrix& d, const Matrix& e);

    ~DualSimplexSolver();

    void solve(int &k, double &y, Matrix &x) override;
    void printDual();
private:
    double targetValue;
    std::vector<int> baseIndices;
    std::vector<int> verifyIndices;
    void pivot(int outBaseIndex, int inBaseIndex);
};

#endif