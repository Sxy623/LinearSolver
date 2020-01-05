#ifndef VANILLA_SIMPLEX_SOLVER_H
#define VANILLA_SIMPLEX_SOLVER_H

#include "solver.h"
#include "utility.h"

// TODO: max
#define M 1e2

class VanillaSimplexSolver : public Solver {
private:
    double value = 0;
    int nonManualVariableCount = 0;
    vector<int> baseIndex;

    void exchange(int inIndex, int outIndex);

public:
    VanillaSimplexSolver(int n, int m, Matrix c, Matrix a, Matrix b, Matrix d, Matrix e);

    ~VanillaSimplexSolver();

    void solve(int &k, double &y, Matrix &x) override;

#ifdef DEBUG

    void printSimplexTable();

#endif
};

#endif