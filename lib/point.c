#include "point.h"

extern Point make_point(scalar x, scalar y, scalar z);
extern Point negative_point(Point p);
extern Point add_points(Point p, Point q);
extern Point multiply_points(Point p, Point q);
extern Vector subtract_points(Point p, Point q);
extern Point cross_product(Point p, Point q);
extern scalar dot_product(Point p, Point q);
extern scalar norm(Point p);
extern Point scale_point(scalar t, Point p);
extern Point unit_point(Point p);
extern int point_is_close_to_zero(Point p);
