#include "dualSimplexSolver.h"
#ifdef PARALLEL
#include "omp.h"
#endif



DualSimplexSolver::DualSimplexSolver(int n, int m, const Matrix& c, const Matrix& a, const Matrix& b, const Matrix& d, const Matrix& e) :
        Solver(n, m, c, a, b, d, e) {
    targetValue = 0.0;
}

DualSimplexSolver::~DualSimplexSolver() = default;

void DualSimplexSolver::solve(int &k, double &y, Matrix &x) {
    // check if dual is feasible
    for (auto j = 0; j < n; j++) {
        if (c[0][j] < -EPS) {
            k = -2;
            return;
        }
    }
    // make it a max problem
    auto constrains = c[0];
    constrains.multi(-1.0);
    // the problem is relaxed and normalized
    for (auto j = n - m; j < n; j++) {
        if (equal(constrains[j], 0.0)) {
            // if it's slack variable
            baseIndices.push_back(j);
        } else {
            k = -2;
            return;
        }
    }
    for (auto j = 0; j <= n - m - 1; j++) {
        verifyIndices.push_back(j);
    }
    for (auto i = 0; i < m; i++) { // for each row
        // reverse the row
        auto rowA = a[i];
        auto rowB = b[i];
        rowA.multi(-1.0);
        rowB.multi(-1.0);
    }
#ifdef DEBUG
    printDual();
#endif  
    while (true) {
        // find the base
        int outBaseIndex = -1;
        int inBaseIndex = -1; // index in verifyIndices vector
        double tb = 0.0;
        int minOutBaseIndex = -1;
        for (auto i = 0; i < m; i++) {
            // always return the smallest one that is smaller than 0
            if (GRE(tb, b[i][0])|| (equal(b[i][0], tb) && baseIndices[i] < minOutBaseIndex)) {
                tb = b[i][0];
                outBaseIndex = i;
                minOutBaseIndex = baseIndices[i];
            }
        }
        if (outBaseIndex == -1) {
            // no negative value in b
            // It's the optimal solution ?
            k = 1;
            y = targetValue;
            for (auto i = 0; i < m; i++) {
                x[0][baseIndices[i]] = b[i][0];
            }
            return;
        }
        // at least one smaller than 0
        // find the smallest absolute ratio
        double ratio = 0;
        int minInBaseIndex = -1;
        for (auto j = 0; j < verifyIndices.size(); j++) {
            // check A_i
            if (GEQ(a[outBaseIndex][verifyIndices[j]], 0.0)) continue;
            double nRatio = std::abs(c[0][verifyIndices[j]] / a[outBaseIndex][verifyIndices[j]]);
            if (inBaseIndex == -1 || GRE(ratio, nRatio) || (equal(nRatio, ratio) && verifyIndices[j] < minInBaseIndex)) {
                inBaseIndex = j;
                ratio = nRatio;
                minInBaseIndex = verifyIndices[j];
            }
        }
        if (inBaseIndex == -1) {
            // A_i >= 0
            k = -1;
            return;
        }
        // the inBase index is found, swap and update
#ifdef DEBUG
        cout << "in: x" << verifyIndices[inBaseIndex] << " out: x" << baseIndices[outBaseIndex] << " Target value: " << targetValue << endl;
#endif
        pivot(outBaseIndex, inBaseIndex);
#ifdef DEBUG
        printDual();
#endif  
    }

}

void DualSimplexSolver::pivot(int outBaseIndex, int inBaseIndex) {
    // update the rows
    double scaleRatio = 1 / a[outBaseIndex][verifyIndices[inBaseIndex]];
    // if want parallel update out base row in advance
    auto rowA = a[outBaseIndex];
    auto rowB = b[outBaseIndex];
    rowA.multi(scaleRatio);
    rowB.multi(scaleRatio);
#ifdef PARALLEL
#pragma omp parallel for
#endif
    for (auto i = 0; i < m; i++) {
        if (i != outBaseIndex) {
            auto anotherA = a[i];
            auto anotherB = b[i];
            double ratio = -anotherA[verifyIndices[inBaseIndex]];
            anotherA.addRow(rowA, ratio);
            anotherB.addRow(rowB, ratio);
        }
#ifdef DEBUG
#ifdef PARALLEL
    printf("parallel: i = %d, run on Thread %d!\n", i, omp_get_thread_num());
#endif
#endif
    }

    // update the constrains
    auto rowC = c[0];
    double ratio = -rowC[verifyIndices[inBaseIndex]];
    rowC.addRow(rowA, ratio);
    targetValue += ratio * rowB[0];
    // swap the basis
    int temp = verifyIndices[inBaseIndex];
    verifyIndices[inBaseIndex] = baseIndices[outBaseIndex];
    baseIndices[outBaseIndex] = temp;
}

void DualSimplexSolver::printDual() {
    printf("============  Simplex Table  ===========\n    ");
    for (int i = 0; i < n; i++) {
        printf(DOUBLE_FORMAT, c[0][i]);
    }
    printf(DOUBLE_FORMAT, targetValue);
    printf("\n");

    for (int i = 0; i < m; i++) {
        printf("x%-3d", baseIndices[i]);
        for (int j = 0; j < n; j++) {
            printf(DOUBLE_FORMAT, a[i][j]);
        }
        printf(DOUBLE_FORMAT, b[i][0]);
        printf("\n");
    }
}
