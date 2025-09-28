#include "hittable_list.h"

struct Hittable_list *new_hittable_node (struct Hittable hittable_object) {
	struct Hittable_list *new_node = (struct Hittable_list *) malloc(sizeof(struct Hittable_list));
	if (!new_node) return NULL;
	new_node -> here = hittable_object;
	new_node -> next = NULL;
	return new_node;
}

void insert_hittable_to_list (struct Hittable_list **head, struct Hittable hittable_object) {
	struct Hittable_list *new_node = new_hittable_node (hittable_object);
	new_node -> next = *head;
	*head = new_node;
}


void delete_hittable_list (struct Hittable_list **head) {
	struct Hittable_list *current_node = *head;
	while (current_node) {
		struct Hittable_list *temp = current_node;
		current_node = current_node -> next;
		free(temp);
	}
	*head = NULL;
}

int ray_hits_hittable_list (Ray r, Interval t_limit, void *hittable_list_void, struct Hit_record *rec) {
	struct Hittable_list *hittable_list = (struct Hittable_list *) hittable_list_void; 
	struct Hit_record temp_rec;
	int hit_anything = 0;
	scalar closest_so_far = t_limit.right;

	while (hittable_list) {
		struct Hittable current_object = hittable_list -> here;	
		if (current_object.hits(r, make_interval(t_limit.left, closest_so_far), current_object.shape, &temp_rec)) {
			hit_anything = 1;
			closest_so_far = temp_rec.ray_t;
			*rec = temp_rec;
		}
		hittable_list = hittable_list -> next; 
	}
	return hit_anything;
}
