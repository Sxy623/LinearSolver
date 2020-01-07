#ifndef BIG_M_SOLVER_H
#define BIG_M_SOLVER_H

#include "solver.h"
#include "utility.h"

// TODO: max
#define M 1e3

class BigMSolver : public Solver {
private:
    double value = 0;
    int nonManualVariableCount = 0;
    vector<int> baseIndex;

    void exchange(int inIndex, int outIndex);

public:
    BigMSolver(int n, int m, Matrix c, Matrix a, Matrix b, Matrix d, Matrix e);

    ~BigMSolver();

    void solve(int &k, double &y, Matrix &x) override;

#ifdef DEBUG

    void printSimplexTable();

#endif
};

#endif