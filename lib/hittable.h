#ifndef HITTABLE_H
#define HITTABLE_H

#include "point.h"
#include "ray.h"
#include "interval.h"
#include "color.h"

struct Hit_record {
	Point ray_hit_point;
	scalar ray_t;
	Point normal;
	struct Material *material;
};

struct Material {
	Color albedo;
	int (*is_scattered)(struct Hit_record *rec, struct Material *parent_material, Ray *scattered_ray, Color *attenuation);
};

struct Hittable {
	void *shape;
	struct Material *material;
	int (*hits)(Ray r, Interval t_limit, void *shape, struct Hit_record *rec);
};

#endif
