#include "row.h"

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