#ifndef _NT_DRAW_BUFFER_H_
#define _NT_DRAW_BUFFER_H_

#include "nt_shared/nt_display_cell.h"
#include <stddef.h>

#define NT_DRAW_BUFFER_WIDTH 250
#define NT_DRAW_BUFFER_HEIGHT 250

typedef struct DrawBuffer
{
    struct NTDisplayCell buffer[NT_DRAW_BUFFER_HEIGHT][NT_DRAW_BUFFER_WIDTH];
    size_t width, height;
} DrawBuffer;

void _nt_draw_buffer_init(DrawBuffer* draw_buffer);

bool _nt_draw_buffer_is_in_bounds(DrawBuffer* draw_buffer, size_t x, size_t y);

#endif // _NT_DRAW_BUFFER_H_
