#include "interval.h"

typedef struct Interval Interval;

Interval make_interval(scalar left, scalar right) {
	Interval I = {left, right};
	return I;
}

int interval_contains(Interval I, scalar x) {
	return I.left <= x && x <= I.right;
}

int interval_contains_strict(Interval I, scalar x) {
	return I.left < x && x < I.right;
}

const Interval empty_interval = {SCALAR_MAX, -SCALAR_MAX};
const Interval full_interval = {-SCALAR_MAX, SCALAR_MAX};
const Interval positive_interval = {0, SCALAR_MAX};

