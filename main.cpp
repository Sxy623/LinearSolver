#include "matrix.h"
#include "vanillaSimplexSolver.h"
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

	VanillaSimplexSolver vanillaSimplexSolver(n, m, c, a, b, d, e);

	cout << "----------Origin----------" << endl;
	vanillaSimplexSolver.print();

	cout << "----------Relaxation----------" << endl;
	vanillaSimplexSolver.relax();
	vanillaSimplexSolver.print();

	return 0;
}