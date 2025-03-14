#include <assert.h>
#include "nt_shared/nt_bounds.h"

static void inline _fix_bounds(NTBounds* bounds)
{
    if((bounds->_start_x == bounds->_end_x) || (bounds->_start_y == bounds->_end_y))
    {
        bounds->_start_x = 0;
        bounds->_start_y = 0;
        bounds->_end_x = 0;
        bounds->_end_y = 0;
    }
}

void nt_bounds_init(NTBounds* bounds, size_t start_x, size_t start_y,
        size_t end_x, size_t end_y, NTBounds* parent_bounds)
{
    nt_bounds_set_values(bounds, start_x, start_y, end_x, end_y);

    bounds->_parent_bounds = parent_bounds;
}

void nt_bounds_init_def(NTBounds* bounds, NTBounds* parent_bounds)
{
    nt_bounds_init(bounds, 0, 0, 0, 0, parent_bounds);
}

void nt_bounds_calculate_size(const NTBounds* bounds,
        size_t* out_width, size_t* out_height)
{
    if(out_width != NULL) *out_width = bounds->_end_x - bounds->_start_x;
    if(out_height != NULL) *out_height = bounds->_end_y - bounds->_start_y;
}

size_t nt_bounds_calculate_width(const NTBounds* bounds)
{
    size_t width, height;
    
    nt_bounds_calculate_size(bounds, &width, &height);

    return width;
}

size_t nt_bounds_calculate_height(const NTBounds* bounds)
{
    size_t width, height;

    nt_bounds_calculate_size(bounds, &width, &height);

    return height;
}

bool nt_bounds_are_equal_size(const NTBounds* bounds1, const NTBounds* bounds2)
{
    size_t b1_width = nt_bounds_calculate_width(bounds1);
    size_t b1_height = nt_bounds_calculate_height(bounds1);

    size_t b2_width = nt_bounds_calculate_width(bounds2);
    size_t b2_height = nt_bounds_calculate_height(bounds2);

    return ((b1_width == b2_width) && (b1_height == b2_height));
}

bool nt_bounds_are_equal(const NTBounds* bounds1, const NTBounds* bounds2)
{
    return ((bounds1->_start_x == bounds2->_start_x) &&
            (bounds1->_start_y == bounds2->_start_y) &&
            (bounds1->_end_x == bounds2->_end_x) &&
            (bounds1->_end_x == bounds2->_end_x));
}

// Coordinates
void nt_bounds_get_values(const NTBounds* bounds,
        size_t* out_start_x, size_t* out_start_y,
        size_t* out_end_x, size_t* out_end_y)
{
    if(out_start_x != NULL) *out_start_x = bounds->_start_x;
    if(out_start_y != NULL) *out_start_y = bounds->_start_y;
    if(out_end_x != NULL) *out_end_x = bounds->_end_x;
    if(out_end_y != NULL) *out_end_y = bounds->_end_y;
}

size_t nt_bounds_get_start_x(const NTBounds* bounds)
{
    return bounds->_start_x;
}

size_t nt_bounds_get_start_y(const NTBounds* bounds)
{
    return bounds->_start_y;
}

size_t nt_bounds_get_end_x(const NTBounds* bounds)
{
    return bounds->_end_x;
}

size_t nt_bounds_get_end_y(const NTBounds* bounds)
{
    return bounds->_end_y;
}

// Absolute coordinates
void nt_bounds_calculate_abs_coordinates(const NTBounds* bounds,
        size_t* out_start_x, size_t* out_start_y,
        size_t* out_end_x, size_t* out_end_y)
{
    size_t abs_start_x = 0, abs_start_y = 0;
    size_t abs_end_x, abs_end_y;

    const NTBounds* curr_bounds = bounds;

    while(curr_bounds != NULL)
    {
        abs_start_x += curr_bounds->_start_x;
        abs_start_y += curr_bounds->_start_y;

        curr_bounds = curr_bounds->_parent_bounds;
    }

    abs_end_x = abs_start_x + bounds->_end_x;
    abs_end_y = abs_start_y + bounds->_end_y;

    if(out_start_x != NULL) *out_start_x = abs_start_x;
    if(out_start_y != NULL) *out_start_y = abs_start_y;
    if(out_end_x != NULL) *out_end_x = abs_end_x;
    if(out_end_y != NULL) *out_end_y = abs_end_y;
}

size_t nt_bounds_calculate_abs_start_x(const NTBounds* bounds)
{
    size_t abs_start_x, abs_start_y, abs_end_x, abs_end_y;

    nt_bounds_calculate_abs_coordinates(bounds, &abs_start_x, &abs_start_y,
            &abs_end_x, &abs_end_y);

    return abs_start_x;
}

size_t nt_bounds_calculate_abs_start_y(const NTBounds* bounds)
{
    size_t abs_start_x, abs_start_y, abs_end_x, abs_end_y;

    nt_bounds_calculate_abs_coordinates(bounds, &abs_start_x, &abs_start_y,
            &abs_end_x, &abs_end_y);

    return abs_start_y;
}

size_t nt_bounds_calculate_abs_end_x(const NTBounds* bounds)
{
    size_t abs_start_x, abs_start_y, abs_end_x, abs_end_y;

    nt_bounds_calculate_abs_coordinates(bounds, &abs_start_x, &abs_start_y,
            &abs_end_x, &abs_end_y);

    return abs_end_x;
}

size_t nt_bounds_calculate_abs_end_y(const NTBounds* bounds)
{
    size_t abs_start_x, abs_start_y, abs_end_x, abs_end_y;

    nt_bounds_calculate_abs_coordinates(bounds, &abs_start_x, &abs_start_y,
            &abs_end_x, &abs_end_y);

    return abs_end_y;
}

void nt_bounds_set_values(NTBounds* bounds,
        size_t new_start_x, size_t new_start_y,
        size_t new_end_x, size_t new_end_y)
{
    // TODO
    assert(new_start_x <= new_end_x);
    assert(new_start_y <= new_end_y);

    bounds->_start_x = new_start_x;
    bounds->_start_y = new_start_y;
    bounds->_end_x = new_end_x;
    bounds->_end_y = new_end_y;

    _fix_bounds(bounds);
}

void nt_bounds_set_start_x(NTBounds* bounds, size_t new_start_x)
{
    bounds->_start_x = new_start_x;
    
    _fix_bounds(bounds);;
}

void nt_bounds_set_start_y(NTBounds* bounds, size_t new_start_y)
{
    bounds->_start_y = new_start_y;
    
    _fix_bounds(bounds);;
}

void nt_bounds_set_end_x(NTBounds* bounds, size_t new_end_x)
{
    bounds->_end_x = new_end_x;
    
    _fix_bounds(bounds);;
}

void nt_bounds_set_end_y(NTBounds* bounds, size_t new_end_y)
{
    bounds->_end_y = new_end_y;
    
    _fix_bounds(bounds);;
}
