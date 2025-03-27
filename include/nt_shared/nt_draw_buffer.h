#ifndef _NT_DRAW_BUFFER_H_
#define _NT_DRAW_BUFFER_H_

#include <stddef.h>

#include "nt_shared/nt_draw_cell.h"

/* NTDrawBuffer represents a dynamic 2D matrix of NTDrawCells.
 *
 * It is primarily used by NTPane as its internal buffer, where the pane can
 * set content of individual cells to reflect what it wants to display on the
 * screen. 
 *
 * This design efficiently manages the grid by minimizing unnecessary memory
 * allocations. The use of extra allocation space means that small increments
 * in grid size do not require immediate reallocation, which improves
 * performance. */

typedef struct NTDrawBuffer
{
    NTDrawCell* _grid;
    size_t _width, _height;
    size_t _alloced_count;
} NTDrawBuffer;

void nt_draw_buffer_init(NTDrawBuffer* draw_buffer);
void nt_draw_buffer_destroy(NTDrawBuffer* draw_buffer);

void nt_draw_buffer_get_size(const NTDrawBuffer* draw_buffer,
        size_t* out_width, size_t* out_height);

size_t nt_draw_buffer_get_width(const NTDrawBuffer* draw_buffer);
size_t nt_draw_buffer_get_height(const NTDrawBuffer* draw_buffer);

void _nt_draw_buffer_set_size(NTDrawBuffer* draw_buffer,
        size_t width, size_t height);

#define nt_draw_buffer_get_cell_at(draw_buff, x, y) \
    (&draw_buff->_grid[y * draw_buff->_width + x])

#endif // _NT_DRAW_BUFFER_H_
