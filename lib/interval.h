#ifndef INTERVAL_H
#define INTERVAL_H
#include "point.h"

struct Interval {scalar left; scalar right;};
typedef struct Interval Interval;

Interval make_interval(scalar left, scalar right);

int interval_contains(Interval I, scalar x);

int interval_contains_strict(Interval I, scalar x);

extern const Interval empty_interval;
extern const Interval full_interval;
extern const Interval positive_interval;

#endif

