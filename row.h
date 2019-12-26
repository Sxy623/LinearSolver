#ifndef ROW_H
#define ROW_H

#include <iostream>
using namespace std;

class Row {
public:
	Row();
	Row(int size, double *data);

	double& operator[](int index);
	double operator[](int index) const;

private:
	int size;
	double *data;
};

#endif