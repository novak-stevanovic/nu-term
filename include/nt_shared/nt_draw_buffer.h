#ifndef _NT_DRAW_BUFFER_H_
#define _NT_DRAW_BUFFER_H_

#include "nt_shared/nt_draw_cell.h"
#include <stddef.h>

#define NT_DRAW_BUFFER_GET_CELL_AT(draw_buff, x, y) \
    (&draw_buff->_grid[y * draw_buff->_width + x])

typedef struct NTDrawBuffer
{
    NTDrawCell* _grid;
    size_t _width, _height;
    size_t _alloced_count;
} NTDrawBuffer;

void nt_draw_buffer_init(NTDrawBuffer* draw_buffer);

void nt_draw_buffer_get_size(const NTDrawBuffer* draw_buffer,
        size_t* out_width, size_t* out_height);

size_t nt_draw_buffer_get_width(const NTDrawBuffer* draw_buffer);
size_t nt_draw_buffer_get_height(const NTDrawBuffer* draw_buffer);

void _nt_draw_buffer_set_size(NTDrawBuffer* draw_buffer,
        size_t width, size_t height);

#endif // _NT_DRAW_BUFFER_H_
