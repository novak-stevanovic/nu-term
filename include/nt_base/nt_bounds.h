#ifndef NT_BOUNDS_H
#define NT_BOUNDS_H

#include <stdbool.h>
#include <stddef.h>

typedef struct NTBounds
{
    size_t _start_x, _start_y; // read-only
    size_t _end_x, _end_y; // read-only
} NTBounds;

void nt_bounds_init(NTBounds* bounds, size_t start_x, size_t start_y, size_t end_x, size_t end_y);
void nt_bounds_init_default(NTBounds* bounds);
void nt_bounds_init_copy(NTBounds* bounds, const NTBounds* src);

size_t nt_bounds_calculate_width(const NTBounds* bounds);
size_t nt_bounds_calculate_height(const NTBounds* bounds);

void nt_bounds_mark_undrawn(NTBounds* bounds);

bool nt_bounds_are_equal(const NTBounds* bounds1, const NTBounds* bounds2);
bool nt_bounds_are_equal_size(const NTBounds* bounds1, const NTBounds* bounds2);

#endif // NT_BOUNDS_H

