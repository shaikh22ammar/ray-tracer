#include "hittable.h"

unsigned int ray_hits_array (struct Hittable_array world, Ray r, struct Hit_record *rec) {
	scalar t_max = SCALAR_MAX;
	scalar t_min = 0.001;
	struct Hit_record temp_rec;
	unsigned int is_scattered_hit = 0;
	for (int i = 0; i < world.length; i++) {
		struct Hittable current = (world.first)[i];
		if ( current.shape -> hits (current.shape, r, t_min, t_max, &temp_rec) ) {
			if (t_max > temp_rec.t) {
				t_max = temp_rec.t;
				is_scattered_hit |= 1;
				*rec = temp_rec;
				if ( current.material -> scatters (current.material, rec) ) {
					is_scattered_hit |= (1 << 1);
				}
				else {
					is_scattered_hit &= ~(1 << 1);
				}
			}
		}
	}
	return is_scattered_hit;
}
