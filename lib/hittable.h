#ifndef HITTABLE_H
#define HITTABLE_H
#include <stdlib.h>
#include "point.h"
#include "ray.h"
#include "interval.h"

struct Hit_record {
	Point ray_hit_point;
	scalar ray_t;
	Point normal;
};

struct Hittable {
	void *shape;
	int (*hits)(Ray r, Interval t_limit, void *shape, struct Hit_record *rec);
};

#endif
