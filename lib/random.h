#ifndef RANDOM_H
#define RANDOM_H

#include "point.h"
#include <stdlib.h>

// returns a random scalar 0 <= < 1
inline scalar random_scalar() {
	return ((scalar) rand()) / (RAND_MAX + 1.0);
}

// returns a random unit vector
inline Vector random_unit_vector() {
	while(1) {
		Vector v = {
			(rand()*2.0)/RAND_MAX - 1, 
			(rand()*2.0)/RAND_MAX - 1, 
			(rand()*2.0)/RAND_MAX - 1};
		scalar len = dot_product(v,v);
		if (len <= 1 && len > 0) {
			len = sqrt(len);
			if (len > 0)
				return scale_point(1.0/len, v);
		}
	}
}

inline Point sample_square() {
	return (Point) {random_scalar() - 0.5, random_scalar() - 0.5, 0};
}

#endif
