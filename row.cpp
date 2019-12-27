#include "row.h"
#include "utility.h"
#include <iostream>
using namespace std;

Row::Row() {
	size = 0;
	data = NULL;
}

Row::Row(int size, double *data): size(size) {
	// Shallow copy
	this->data = data;
}

double& Row::operator[](int index) {
	if (index < 0 || index >= size) {
		cerr << "Error!" << endl;
		exit(0);
	}
	return data[index];
}

double Row::operator[](int index) const {
	if (index < 0 || index >= size) {
		cerr << "Error!" << endl;
		exit(0);
	}
	return data[index];
}

void Row::printPolynomial() {
	for (int i = 0; i < size; i++) {
		if (i == 0) {
			printItem(data[i], i);
			continue;
		}
		printf(" + ");
		printItem(data[i], i);
	}
}