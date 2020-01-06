#include "vanillaSimplexSolver.h"
#include "utility.h"
#ifdef PARALLEL
#include "omp.h"
#endif

VanillaSimplexSolver::VanillaSimplexSolver(int n, int m, Matrix c, Matrix a, Matrix b, Matrix d,
                                           Matrix e) :
        Solver(n, m, c, a, b, d, e) {}

VanillaSimplexSolver::~VanillaSimplexSolver() = default;

void VanillaSimplexSolver::exchange(int inIndex, int outIndex) {
//#ifdef DEBUG
    cout << outIndex << " - in: x" << inIndex << " out: x" << baseIndex[outIndex] << endl;
//#endif
    baseIndex[outIndex] = inIndex;
    Row pivot = a[outIndex];
    Row pivotB = b[outIndex];
    // normalize to one
    double toOneRatio = 1 / a[outIndex][inIndex];
    pivot.multi(toOneRatio);
    pivotB.multi(toOneRatio);
    // normalize other rows to zero
#ifdef PARALLEL
#pragma omp parallel for default(none) shared(pivot) shared(pivotB) shared(inIndex) shared(outIndex)
#endif
    for (int i = 0; i < m; i++) {
        if (i != outIndex) {
            Row another = a[i];
            Row anotherB = b[i];
            double ratio = -another[inIndex];
            another.addRow(pivot, ratio);
            anotherB.addRow(pivotB, ratio);
        }
#ifdef DEBUG
#ifdef PARALLEL
        printf("parallel: i = %d, run on Thread %d!\n", i, omp_get_thread_num());
#endif
#endif
    }
    // transform checked number to zero
    Row cRow = c[0];
    double ratio = -cRow[inIndex];
    cRow.addRow(pivot, ratio);
    value += pivotB[0] * ratio;
}

void VanillaSimplexSolver::solve(int &k, double &y, Matrix &x) {
    nonManualVariableCount = n;
    // add artificial variables
    Matrix zero = Matrix(m, 1);
    Matrix one = Matrix(1, 1, 1);
    for (int i = 0; i < m; i++) {
        a.appendColumn(zero);
        a[i][n] = 1;
        c.appendColumn(one);
        e.appendColumn(one);
        baseIndex.push_back(n);
        n++;
    }
    // to max format
    Row checkedArray = c[0];
    for (int i = 0; i < n; i++) {
        checkedArray[i] = -checkedArray[i];
    }
//    printSimplexTable();

    // 1st stage: min sum of artificial variables
    Matrix oldCheckedMat(c);
    for (int i = 0; i < nonManualVariableCount; i++) {
        checkedArray[i] = 0;
    }
    // normalize checked number of artificial variables
    for (int i = 0; i < m; i++) {
        auto rowi = a[i];
        checkedArray.addRow(rowi, 1);
        double delta = b[i][0];
        value += delta;
    }
    solveInternal();
    if (!equal(value, 0)) {
        k = -1;
        return;
    }
    // check if there is an artificial variable in base
    for (int i = 0; i < m; i++) {
        if (baseIndex[i] >= nonManualVariableCount) {
            for (int j = 0; j < nonManualVariableCount; j++) {
                if (!equal(checkedArray[j], 0)) {
                    exchange(j, i);
                    break;
                }
            }

        }
    }
//    printSimplexTable();
    // recover checked array
    for (int i = 0; i < nonManualVariableCount; i++) {
        c[0][i] = oldCheckedMat[0][i];
    }
    for (int i = nonManualVariableCount; i < n; i++) {
        c[0][i] = 0;
    }
    n = nonManualVariableCount;
    cout << "2nd" << endl;
//    printSimplexTable();
    // 2nd stage: solve others
    // normalize checked number
    for (int i = 0; i < m; i++) {
        int base = baseIndex[i];
        double baseCheckedNum = checkedArray[base];
        if (baseCheckedNum != 0) {
            auto currentRow = a[i];
            checkedArray.addRow(currentRow, -baseCheckedNum);
            value -= b[i][0] * baseCheckedNum;
        }
    }
//    printSimplexTable();
    // solve!
    bool notUnbound = solveInternal();
    if (!notUnbound) {
        k = 0;
        return;
    }
    // output answer
    k = 1;
    for (int i = 0; i < m; i++) {
        int base = baseIndex[i];
        x[0][base] = b[i][0];
    }
    y = value;
}


void VanillaSimplexSolver::printSimplexTable() {
//#ifdef DEBUG
    printf("============  Simplex Table  ===========\n    ");
    for (int i = 0; i < n; i++) {
        printf(DOUBLE_FORMAT, c[0][i]);
    }
    printf(DOUBLE_FORMAT, value);
    printf("\n");

    for (int i = 0; i < m; i++) {
        printf("x%-3d", baseIndex[i]);
        for (int j = 0; j < n; j++) {
            printf(DOUBLE_FORMAT, a[i][j]);
        }
        printf(DOUBLE_FORMAT, b[i][0]);
        printf("\n");
    }
//#endif
}

bool VanillaSimplexSolver::solveInternal() {
    auto checkedArray = c[0];
    int count = 0;
    while (true) {
        // get max
        cout << count++ << " " << value << " " << n << endl;
        int inIndex = -1;
        double maxCheckedNum = 0;
        for (int i = 0; i < n; i++) {
            double num = checkedArray[i];
            if (num > 0) {
                // judge unbound
                bool flag = true;
                for (int j = 0; j < m; j++) {
                    if (a[j][i] > 0) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    // All numbers in column i are <= 0: unbound!
                    return false;
                }
                // get max index
                if (num > maxCheckedNum) {
                    inIndex = i;
                    maxCheckedNum = num;
                }
            }
        }
        if (inIndex == -1) {
            return true;
        }
        int outIndex = -1;
        double minRatio = 0;
        int minOutIndex = INT_MAX;
        for (int i = 0; i < m; i++) {
            double aik = a[i][inIndex];
            if (aik <= 0) continue;
            double ratio = b[i][0] / aik;
            if (outIndex == -1 || minRatio > ratio || (equal(minRatio, ratio) && baseIndex[i] < minOutIndex)) {
                minRatio = ratio;
                minOutIndex = baseIndex[i];
                outIndex = i;
            }
        }
        // outIndex == -1 is impossible, due to this case is unbound!
        exchange(inIndex, outIndex);

#ifdef DEBUG
        printSimplexTable();
#endif
    }
}
