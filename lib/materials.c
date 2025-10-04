#include "materials.h"
#include <stdio.h>
#include <stdlib.h>
#include "random.h"

static int lambertian_scatter (struct Material *self, struct Hit_record *rec) {
	Vector scatter_direction = add_points(rec->normal, random_unit_vector());
	rec->scattered_ray = make_ray(rec->ray_hit_point, scatter_direction);
	rec->attenuation = self->albedo;
	return 1;	
}

static Vector reflection_direction (Vector in, Vector normal) {
	return subtract_points (
				in, 
				scale_point(
					2 * dot_product(in, normal), 
					normal));
}

static int mettalic_scatter (struct Material *self, struct Hit_record *rec) {
	scalar fuzziness = self->params[0];
	Vector scatter_direction = unit_point(reflection_direction(rec->ray_hit_point, rec->normal));
	scatter_direction = add_points(
			scatter_direction,
			scale_point(fuzziness, random_unit_vector()));
	rec->scattered_ray = make_ray(rec->ray_hit_point, scatter_direction);
	rec->attenuation = self->albedo;
	return (dot_product(scatter_direction, rec->normal) > 0);
}

struct Material *make_lambertian_material (Color albedo) {
	struct Material *lambertian = (struct Material *) malloc (sizeof(struct Material) );
	lambertian->albedo = albedo;
	lambertian->scatters = &lambertian_scatter;
	return lambertian;
}

struct Material *make_reflective_material (Color albedo, scalar fuzziness) {
	struct Material *metal = (struct Material *) malloc (sizeof(struct Material) + sizeof(scalar));
	metal->albedo = albedo;
	(metal->params)[0] = fuzziness;
	(metal->scatters) = &mettalic_scatter;
	return metal;
}
