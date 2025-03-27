#include "nt_shared/nt_draw_buffer.h"

#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "nt_shared/nt_shared.h"
#include "nt_util/nt_log.h"

/* -------------------------------------------------------------------------- */

#define SHRINK_THRESHOLD_FACTOR 2.5
#define EXPAND_FACTOR 2

static void _handle_free(NTDrawBuffer* draw_buffer);

static void _handle_malloc(NTDrawBuffer* draw_buffer,
        size_t width, size_t height);

/* -------------------------------------------------------------------------- */

void nt_draw_buffer_init(NTDrawBuffer* draw_buffer)
{
    draw_buffer->_height = 0;
    draw_buffer->_width = 0;
    draw_buffer->_alloced_count = 0;
    draw_buffer->_grid = NULL;
}

void nt_draw_buffer_destroy(NTDrawBuffer* draw_buffer)
{
    _handle_free(draw_buffer);
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
    if((height == draw_buffer->_height) && (width == draw_buffer->_width))
        return;

    if((width == 0) || (height == 0))
        _handle_free(draw_buffer);
    else
    {
        if(draw_buffer->_grid != NULL)
            free(draw_buffer->_grid);
        
        _handle_malloc(draw_buffer, width, height);
    }
}

/* -------------------------------------------------------------------------- */

static void _handle_free(NTDrawBuffer* draw_buffer)
{
    draw_buffer->_width = 0;
    draw_buffer->_height = 0;
    draw_buffer->_alloced_count = 0;

    if(draw_buffer->_grid != NULL)
        free(draw_buffer->_grid);

    draw_buffer->_grid = NULL;
}

static void _handle_malloc(NTDrawBuffer* draw_buffer,
        size_t new_width, size_t new_height)
{
    size_t req_alloced_count = new_height * new_width;
    size_t lower_bound = floor(draw_buffer->_alloced_count /
            SHRINK_THRESHOLD_FACTOR);

    if((req_alloced_count > draw_buffer->_alloced_count) ||
            (req_alloced_count < (lower_bound)))
    {
        size_t new_alloced_count = ceil(new_width * new_height * EXPAND_FACTOR);

        if(new_alloced_count > (NT_DISPLAY_MAX_HEIGHT * NT_DISPLAY_MAX_WIDTH))
            new_alloced_count = NT_DISPLAY_MAX_HEIGHT * NT_DISPLAY_MAX_WIDTH;

        size_t new_alloced_size = new_alloced_count * sizeof(struct NTDrawCell);

        // TODO: handle fail
        draw_buffer->_grid = malloc(new_alloced_size);

        draw_buffer->_alloced_count = new_alloced_count;
    }

    draw_buffer->_width = new_width;
    draw_buffer->_height = new_height;
}
