#include "matrix.h"
#include "bigMSolver.h"
#include "doubleStageSolver.h"
#include "dualSimplexSolver.h"
#include <iostream>

using namespace std;

int main() {

    int n, m;
    cin >> n >> m;

    Matrix c(1, n);
    cin >> c;

    Matrix mat(m, n + 2);
    cin >> mat;

    Matrix a = mat.getColumns(0, n);
    Matrix b = mat.getColumn(n);
    Matrix d = mat.getColumn(n + 1);

    Matrix e(1, n);
    cin >> e;

    int k;
    double y;
    Matrix x(1, n + 2 * m);

    /* Simplex Method - Big M */

#ifdef DEBUG
    cout << endl;
    cout << ">>> Simplex Method - Big M" << endl;
#endif

#ifdef SIMPLEX_BIG_M
    BigMSolver bigMSolver(n, m, c, a, b, d, e);
#ifdef DEBUG
    cout << "===============  Origin  ===============" << endl;
    bigMSolver.print();

    cout << "=============  Relaxation  =============" << endl;
    bigMSolver.relax();
    bigMSolver.print();

    cout << "============  Normalization  ===========" << endl;
    bigMSolver.normalize();
    bigMSolver.print();
#else
    bigMSolver.normalize();
#endif
    bigMSolver.solve(k, y, x);
    bigMSolver.recover(x);
    cout << k << endl;
    if (k == 1) {
        cout << y << endl;
        for (int i = 0; i < n; i++) {
            cout << x[0][i] << " ";
        }
    }
    cout << endl;
#endif

    /* Simplex Method - Double Stage */

#ifdef DEBUG
    cout << endl;
    cout << ">>> Simplex Method - Double Stage" << endl;
#endif

#ifdef SIMPLEX_DOUBLE_STAGE
    DoubleStageSolver doubleStageSolver(n, m, c, a, b, d, e);
#ifdef DEBUG
    cout << "===============  Origin  ===============" << endl;
    doubleStageSolver.print();

    cout << "=============  Relaxation  =============" << endl;
    doubleStageSolver.relax();
    doubleStageSolver.print();

    cout << "============  Normalization  ===========" << endl;
    doubleStageSolver.normalize();
    doubleStageSolver.print();
#else
    doubleStageSolver.normalize();
#endif
    doubleStageSolver.solve(k, y, x);
    doubleStageSolver.recover(x);
    cout << k << endl;
    if (k == 1) {
        cout << y << endl;
        for (int i = 0; i < n; i++) {
            cout << x[0][i] << " ";
        }
    }
    cout << endl;
#endif

    /* Dual Simplex Method */

#ifdef DEBUG
    cout << endl;
    cout << ">>> Dual Simplex Method" << endl;
#endif

#ifdef DUAL
    DualSimplexSolver dualSimplexSolver(n, m, c, a, b, d, e);
#ifdef DEBUG
    cout << "===============  Origin  ===============" << endl;
    dualSimplexSolver.print();

    cout << "=============  Relaxation  =============" << endl;
    dualSimplexSolver.relax();
    dualSimplexSolver.print();

    cout << "============  Normalization  ===========" << endl;
    dualSimplexSolver.normalize();
    dualSimplexSolver.print();
#else
    dualSimplexSolver.normalize();
#endif
    dualSimplexSolver.solve(k, y, x);
    dualSimplexSolver.recover(x);
    cout << k << endl;
    if (k == 1) {
        cout << y << endl;
        for (int i = 0; i < n; i++) {
            cout << x[0][i] << " ";
        }
    }
    cout << endl;
#endif

    return 0;
}