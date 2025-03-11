#include <assert.h>
#include <stdlib.h>

#include "nt_shared/nt_draw_buffer.h"
#include "nt_shared/nt_display_cell.h"

void nt_draw_buffer_init(NTDrawBuffer* draw_buffer)
{
    draw_buffer->_height = 0;
    draw_buffer->_width = 0;
    draw_buffer->_buffer = NULL;
}

void nt_draw_buffer_set_size(NTDrawBuffer* draw_buffer, size_t width, size_t height)
{
    if((width == 0) || (height == 0)) // set to NULL
    {
        if(draw_buffer->_buffer != NULL)
            free(draw_buffer->_buffer);

        draw_buffer->_buffer = NULL;
        draw_buffer->_height = 0;
        draw_buffer->_width = 0;
    }
    else // realloc
    {
        size_t new_size = height * width * sizeof(NTDisplayCell);

        if(draw_buffer->_buffer == NULL)
            draw_buffer->_buffer = malloc(new_size);
        else
            draw_buffer->_buffer = realloc(draw_buffer->_buffer, new_size);

        assert(draw_buffer->_buffer != NULL);
    }

}
