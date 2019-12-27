#include "utility.h"
#include <cmath>

bool equal(double a, double b) {
	return fabs(a - b) < EPS;
}