#ifndef DOUBLE_STAGE_SOLVER_H
#define DOUBLE_STAGE_SOLVER_H

#include "solver.h"
#include "utility.h"

// TODO: max
#define M 1e3

class DoubleStageSolver : public Solver {
private:
    double value = 0;
    int nonManualVariableCount = 0;
    vector<int> baseIndex;

    void exchange(int inIndex, int outIndex);

    // return false: unbound
    bool solveInternal();

public:
    DoubleStageSolver(int n, int m, Matrix c, Matrix a, Matrix b, Matrix d, Matrix e);

    ~DoubleStageSolver();

    void solve(int &k, double &y, Matrix &x) override;

    void printSimplexTable();

};

#endif