#include "solver.h"
#include "utility.h"
#include <iostream>
using namespace std;

Solver::Solver(int n, int m, Matrix c, Matrix a, Matrix b, Matrix d, Matrix e): 
	n(n), m(m), c(c), a(a), b(b), d(d), e(e) {
	negative.clear();
	noConstraints.clear();
}

Solver::~Solver() {}

void Solver::relax() {
	Matrix zero = Matrix(1, 1);
	Matrix one = Matrix(1, 1, 1);
	for (int i = 0; i < m; i++) {
		if (equal(d[i][0], 0)) continue;
		if (equal(d[i][0], 1)) {
			n++;
			c.appendColumn(zero);
			e.appendColumn(one);
			Matrix newColumn(m, 1);
			newColumn[i][0] = -1;
			a.appendColumn(newColumn);
			d[i][0] = 0;
			continue;
		}
		if (equal(d[i][0], -1)) {
			n++;
			c.appendColumn(zero);
			e.appendColumn(one);
			Matrix newColumn(m, 1);
			newColumn[i][0] = 1;
			a.appendColumn(newColumn);
			d[i][0] = 0;
			continue;
		}
	}
}

void Solver::normalize() {
	Matrix one = Matrix(1, 1, 1);
	relax();
	for (int i = 0; i < m; i++) {
		if (b[i][0] >= 0) continue;
		 b[i][0] *= -1;
		 for (int j = 0; j < n; j++) {
		 	a[i][j] *= -1;
		 }
	}
	for (int j = 0; j < n; j++) {
		if (equal(e[0][j], 1)) continue;
		if (equal(e[0][j], -1)) {
			c[0][j] *= -1;
			e[0][j] = 1;
			for (int i = 0; i < m; i++) {
				a[i][j] *= -1;
			}
			negative.push_back(j);
			continue;
		}
		if (equal(e[0][j], 0)) {
			n++;
			c.appendColumn(one);
			c[0][n - 1] = c[0][j] * -1;
			e[0][j] = 1;
			e.appendColumn(one);
			Matrix newColumn = a.getColumn(j) * -1;
			a.appendColumn(newColumn);
			noConstraints.push_back(make_pair(j, n - 1));
			continue;
		}
	}
}

void Solver::print() {
	cout << "min" << endl;
	c[0].printPolynomial();
	cout << endl;
	cout << "s.t." << endl;
	for (int i = 0; i < m; i++) {
		a[i].printPolynomial();
		printSign(d[i][0]);
		printDouble(b[i][0]);
		cout << endl;
	}
	cout << "&&" << endl;
	for (int i = 0; i < n; i++) {
		printConstraint(i, e[0][i]);
		cout << endl;
	}
}