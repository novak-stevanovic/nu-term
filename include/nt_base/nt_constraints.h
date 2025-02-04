#ifndef NT_CONSTRAINTS_H
#define NT_CONSTRAINTS_H

#include <stdlib.h>

struct NTConstraints
{
    size_t _min_size_x, _min_size_y; // read-only
    size_t _max_size_x, _max_size_y; // read-only

    ssize_t used_x, used_y;
};

void nt_constraints_init(struct NTConstraints* constraints,
        size_t min_size_x, size_t min_size_y,
        size_t max_size_x, size_t max_size_y);

int nt_constraints_check_consistency(struct NTConstraints* constraints);

#endif
