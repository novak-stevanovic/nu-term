#include "nt_base/nt_bounds.h"

void nt_bounds_init(NTBounds* bounds, size_t start_x, size_t start_y, size_t end_x, size_t end_y)
{
    if(((start_x == 0) && (end_x == 0)) ||
        ((start_y == 0) && (end_y == 0)))
    {
        start_x = 0;
        start_y = 0;
        end_x = 0;
        end_y = 0;
    }

    bounds->_start_x = start_x;
    bounds->_start_y = start_y;
    bounds->_end_x = end_x;
    bounds->_end_y = end_y;

}

void nt_bounds_init_default(NTBounds* bounds)
{
    nt_bounds_init(bounds, 0, 0, 0, 0);
}

void nt_bounds_init_copy(NTBounds* bounds, const NTBounds* src)
{
    nt_bounds_init(bounds, src->_start_x, src->_start_y, src->_end_x, src->_end_y);
}

void nt_bounds_mark_undrawn(NTBounds* bounds)
{
    nt_bounds_init(bounds, 0, 0, 0, 0);
}

size_t nt_bounds_calculate_width(const NTBounds* bounds)
{
    return bounds->_end_x - bounds->_start_x; 
}

size_t nt_bounds_calculate_height(const NTBounds* bounds)
{
    return bounds->_end_y - bounds->_start_y; 
}

bool nt_bounds_are_equal(const NTBounds* bounds1, const NTBounds* bounds2)
{
    return ((bounds1->_start_x == bounds2->_start_x) && 
    (bounds1->_start_y == bounds2->_start_y) && 
    (bounds1->_end_x == bounds2->_end_x) && 
    (bounds1->_end_x == bounds2->_end_x));
}

bool nt_bounds_are_equal_size(const NTBounds* bounds1, const NTBounds* bounds2)
{
    return ((nt_bounds_calculate_height(bounds1) == nt_bounds_calculate_height(bounds2)) &&
            nt_bounds_calculate_width(bounds1) == nt_bounds_calculate_width(bounds2));
}
