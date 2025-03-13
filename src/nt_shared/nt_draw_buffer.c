#include <assert.h>
#include <stdlib.h>

#include "nt_shared/nt_draw_buffer.h"

void nt_draw_buffer_init(NTDrawBuffer* draw_buffer)
{
    draw_buffer->_height = 0;
    draw_buffer->_width = 0;
    draw_buffer->_grid = NULL;
}

void nt_draw_buffer_get_size(const NTDrawBuffer* draw_buffer,
        size_t* out_width, size_t* out_height)
{
    if(out_width != NULL) *out_width = draw_buffer->_width;
    if(out_height != NULL) *out_height = draw_buffer->_height;
}

size_t nt_draw_buffer_get_width(const NTDrawBuffer* draw_buffer)
{
    return draw_buffer->_width;
}

size_t nt_draw_buffer_get_height(const NTDrawBuffer* draw_buffer)
{
    return draw_buffer->_height;
}

void _nt_draw_buffer_set_size(NTDrawBuffer* draw_buffer,
        size_t width, size_t height)
{
    if((width == 0) || (height == 0))
    {
        draw_buffer->_width = 0;
        draw_buffer->_height = 0;

        if(draw_buffer->_grid != NULL)
            free(draw_buffer->_grid);

        draw_buffer->_grid = NULL;
    }
    else
    {
        draw_buffer->_width = width;
        draw_buffer->_height = height;

        assert(width < 1000);
        assert(height < 1000);

        if(draw_buffer->_grid != NULL)
        {
            draw_buffer->_grid = realloc(draw_buffer->_grid,
                    sizeof(NTDrawCell) * width * height);
        }
        else
        {
            draw_buffer->_grid = malloc(sizeof(NTDrawCell) * width * height);
        }
    }
}
