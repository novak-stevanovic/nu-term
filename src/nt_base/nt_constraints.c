#include <assert.h>
#include <stdio.h>

#include "nt_base/nt_constraints.h"

void nt_constraints_init(struct NTConstraints* constraints,
        size_t min_width, size_t min_height,
        size_t max_width, size_t max_height)
{
    assert(constraints != NULL);

    if(((min_width == 0) && (max_width == 0)) || ((min_height == 0) && (max_height == 0)))
    {
        constraints->_min_width = 0;
        constraints->_max_width = 0;
        constraints->_min_height = 0;
        constraints->_max_height = 0;
    }
    else
    {
        constraints->_min_width = min_width;
        constraints->_min_height = min_height;
        constraints->_max_width = max_width;
        constraints->_max_height = max_height;

        // printf("CON: %d %d %d %d\n", min_width, min_height, max_width, max_height);
    }

    assert(nt_constraints_check_consistency(constraints));

    constraints->_used_x = -1;
    constraints->_used_y = -1;
}

int nt_constraints_check_consistency(struct NTConstraints* constraints)
{
    assert(constraints != NULL);
    
    return ((constraints->_max_width >= constraints->_min_width) && (constraints->_max_height >= constraints->_min_height));
}

int nt_constraints_has_object_been_drawn(size_t used_x, size_t used_y)
{
    return ((used_x != 0) && (used_y != 0));
}

int nt_constraints_has_object_been_drawn_c(struct NTConstraints* constraints)
{
    if(constraints == NULL) return NULL;


    return nt_constraints_has_object_been_drawn(constraints->_used_x, constraints->_used_y);
}


void nt_constraints_set_values(struct NTConstraints* constraints, size_t used_x, size_t used_y)
{
    assert(constraints != NULL);
    constraints->_used_x = used_x;
    constraints->_used_y = used_y;
}
