#include "nt_core/_nt_draw_buffer.h"

void _nt_draw_buffer_init(NTDrawBuffer* draw_buffer)
{
    draw_buffer->height = 0;
    draw_buffer->width = 0;

    size_t i, j;
    for(i = 0; i < NT_DRAW_BUFFER_HEIGHT; i++)
    {
        for(j = 0; j < NT_DRAW_BUFFER_WIDTH; j++)
            nt_display_cell_init_default(&draw_buffer->buffer[i][j]);
    }
}

bool _nt_draw_buffer_is_in_bounds(NTDrawBuffer* draw_buffer, size_t x, size_t y)
{
    return ((draw_buffer->width > x) && (draw_buffer->height > y));
}
