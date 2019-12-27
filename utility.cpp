#include "utility.h"
#include <cmath>
#include <cstdio>

bool equal(double a, double b) {
	return fabs(a - b) < EPS;
}

void printSign(double flag) {
	if (equal(flag, 0)) printf("  = ");
	else if (equal(flag, 1)) printf(" >= ");
	else printf(" <= ");
}
void printDouble(double x) {
	printf(DOUBLE_FORMAT, x);
}

void printItem(double coefficient, int index) {
	printf(ITEM_FORMAT, coefficient, index);
}

void printConstraint(int index, double flag) {
	printf(ITEM_NO_COEFFICIENT_FORMAT, index);
	printSign(flag);
	printf(DOUBLE_FORMAT, 0.0);
}