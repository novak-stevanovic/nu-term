#ifndef _NT_BOUNDS_H_
#define _NT_BOUNDS_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct NTBounds
{
    struct NTBounds* _parent_bounds;

    size_t _start_x, _start_y;
    size_t _end_x, _end_y;
} NTBounds;

// Init
void nt_bounds_init(NTBounds* bounds,
        size_t start_x, size_t start_y,
        size_t end_x, size_t end_y,
        NTBounds* parent_bounds);
void nt_bounds_init_def(NTBounds* bounds, NTBounds* parent_bounds);

// Getters
void nt_bounds_get_values(const NTBounds* bounds,
        size_t* out_start_x, size_t* out_start_y,
        size_t* out_end_x, size_t* out_end_y);
size_t nt_bounds_get_start_x(const NTBounds* bounds);
size_t nt_bounds_get_start_y(const NTBounds* bounds);
size_t nt_bounds_get_end_x(const NTBounds* bounds);
size_t nt_bounds_get_end_y(const NTBounds* bounds);

// Setters
void nt_bounds_set_values(NTBounds* bounds,
        size_t new_start_x, size_t new_start_y,
        size_t new_end_x, size_t new_end_y);
void nt_bounds_set_start_x(NTBounds* bounds, size_t new_start_x);
void nt_bounds_set_start_y(NTBounds* bounds, size_t new_start_y);
void nt_bounds_set_end_x(NTBounds* bounds, size_t new_end_x);
void nt_bounds_set_end_y(NTBounds* bounds, size_t new_end_y);

// Absolute coordinates
void nt_bounds_calculate_abs_coordinates(const NTBounds* bounds,
        size_t* out_start_x, size_t* out_start_y,
        size_t* out_end_x, size_t* out_end_y);
size_t nt_bounds_calculate_abs_start_x(const NTBounds* bounds);
size_t nt_bounds_calculate_abs_start_y(const NTBounds* bounds);
size_t nt_bounds_calculate_abs_end_x(const NTBounds* bounds);
size_t nt_bounds_calculate_abs_end_y(const NTBounds* bounds);

// Size
void nt_bounds_calculate_size(const NTBounds* bounds, size_t* out_width, size_t* out_height);
size_t nt_bounds_calculate_width(const NTBounds* bounds);
size_t nt_bounds_calculate_height(const NTBounds* bounds);

bool nt_bounds_are_equal_size(const NTBounds* bounds1, const NTBounds* bounds2);

// Doesnt take into account parent, abs bounds
// bool nt_bounds_are_equal(const NTBounds* bounds1, const NTBounds* bounds2);

#endif // _NT_BOUNDS_H_

