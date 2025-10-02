#include "random.h"
#include <stdlib.h> // for rand()
#include <math.h> // sqrt() for unit_vector

scalar random_scalar() {
	return ((scalar) rand()) / (RAND_MAX + 1.0);
}

Vector random_unit_vector() {
	while(1) {
		Vector v = make_point((rand()*2.0)/RAND_MAX - 1, (rand()*2.0)/RAND_MAX - 1, (rand()*2.0)/RAND_MAX - 1);
		scalar len = dot_product(v,v);
		if (len <= 1 && len > 0) {
			len = sqrt(len);
			if (len > 0)
				return scale_point(1.0/len, v);
		}
	}
}


Vector random_unit_vector_on_hemisphere(Vector p) {
	Vector v = random_unit_vector();
	if (dot_product(v, p) >= 0)
		return v;
	return scale_point(-1.0, v);
}

