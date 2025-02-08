#include <assert.h>
#include <stdio.h>

#include "nt_base/nt_constraints.h"

void nt_constraints_init(struct NTConstraints* constraints,
        size_t min_width, size_t min_height,
        size_t max_width, size_t max_height)
{
    assert(constraints != NULL);

    // assert(nt_constraints_check_consistency(constraints));

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
    constraints->used_x = -1;
    constraints->used_y = -1;
}

void nt_constraints_normalize_used(struct NTConstraints* constraints)
{
    if(constraints->used_x == 0) constraints->used_y = 0;
    else if(constraints->used_y == 0) constraints->used_x = 0;
}

int nt_constraints_check_consistency(struct NTConstraints* constraints)
{
    assert(constraints != NULL);
    
    return ((constraints->_max_width >= constraints->_min_width) && (constraints->_max_height >= constraints->_min_height));
}
