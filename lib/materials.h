#ifndef MATERIALS_H
#define MATERIALS_H 

#include "hittable.h"
#include "random.h"

int lambertian_scatter (
		struct Hit_record *rec, 
		struct Material *parent_material,
		Ray *scattered_ray, Color *attenuation
		) {
	Vector scatter_direction = add_points(rec->normal, random_unit_vector());
	*scattered_ray = make_ray(rec->ray_hit_point, scatter_direction);
	*attenuation = parent_material -> albedo;
	return 1;	
}

Vector reflection_direction (Vector in, Vector normal) {
	return subtract_points (
				in, 
				scale_point(
					2 * dot_product(in, normal), 
					normal));
}

int reflective_scatter (
		struct Hit_record *rec, 
		struct Material *parent_material,
		Ray *scattered_ray, Color *attenuation
		) {
	Vector scatter_direction = reflection_direction(rec->ray_hit_point, rec->normal);
	*scattered_ray = make_ray(rec->ray_hit_point, scatter_direction);
	*attenuation = parent_material->albedo;
	return 1;
}

struct Material make_lambertian_material(Color albedo) {
	struct Material lambertian = {albedo, &lambertian_scatter};
	return lambertian;
}


struct Material make_metal(Color albedo) {
	struct Material metal = {albedo, &reflective_scatter};
	return metal;
}

#endif
