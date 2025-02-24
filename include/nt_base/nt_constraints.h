#ifndef NT_CONSTRAINTS_H
#define NT_CONSTRAINTS_H

#include <stdlib.h>

struct NTObject;

struct NTConstraints
{
    size_t _min_width, _min_height; // read-only
    size_t _max_width, _max_height; // read-only
};

void nt_constraints_init(struct NTConstraints* constraints,
        size_t min_width, size_t min_height,
        size_t max_width, size_t max_height);

int nt_constraints_check_consistency(struct NTConstraints* constraints);

size_t nt_constraints_determine_min_size(size_t constraint_min_size, size_t obj_min_size, size_t constraint_max_size);
size_t nt_constraints_determine_max_size(size_t constraint_max_size, size_t obj_max_size, size_t constraint_min_size);

void nt_constraints_apply_object_restrictions(struct NTConstraints* constraints, struct NTObject* object);

// int nt_constraints_has_object_been_drawn(size_t used_x, size_t used_y);
// int nt_constraints_has_object_been_drawn_c(struct NTConstraints* constraints);

#endif
