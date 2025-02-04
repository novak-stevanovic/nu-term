#include <assert.h>

#include "nt_base/nt_constraints.h"

void nt_constraints_init(struct NTConstraints* constraints,
        size_t start_x, size_t start_y,
        size_t min_size_x, size_t min_size_y,
        size_t max_size_x, size_t max_size_y)
{
    assert(constraints != NULL);

    constraints->_start_x = start_x;
    constraints->_start_y = start_y;
    constraints->_min_size_x = min_size_x;
    constraints->_min_size_y = min_size_y;
    constraints->_max_size_x = max_size_x;
    constraints->_max_size_y = max_size_y;

    assert(nt_constraints_check_consistency(constraints));

    constraints->used_x = -1;
    constraints->used_y = -1;
}

int nt_constraints_check_consistency(struct NTConstraints* constraints)
{
    assert(constraints != NULL);
    
    return ((constraints->_max_size_x >= constraints->_min_size_x) && 
        (constraints->_max_size_y >= constraints->_min_size_y) &&
        ((constraints->_min_size_x != 0) || (constraints->_min_size_x == 0 && constraints->_max_size_x != 0)) &&
        ((constraints->_min_size_y != 0) || (constraints->_min_size_y == 0 && constraints->_max_size_y != 0)));
}
