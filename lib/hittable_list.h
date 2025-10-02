#ifndef HITTABLELIST_H
#define HITTABLELIST_H
#include "hittable.h"

struct Hittable_list {
	struct Hittable here;
	struct Hittable_list *next;
};

struct Hittable_list *new_hittable_node (struct Hittable hittable_object);

void insert_hittable_to_list (struct Hittable_list **head, struct Hittable hittable_object);

void delete_hittable_list (struct Hittable_list **head);

int ray_hits_hittable_list (Ray r, Interval t_limit, void *hittable_list_void, struct Hit_record *rec);

#endif
