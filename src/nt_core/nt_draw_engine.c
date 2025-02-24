#include <stdlib.h>

#include "nt_core/nt_draw_engine.h"
#include "nt_base/nt_constraints.h"
#include "nt_base/nt_object.h"
#include "nt_base/nt_window.h"
#include "nt_core/_nt_draw_buffer.h"
#include "nt_core/nt_color.h"
#include "nt_core/nt_cursor.h"
#include "nt_core/nt_display.h"
#include "nt_log.h"
#include "nt_shared/nt_display_cell.h"
#include "nt_core/_nt_draw_list.h"

static NTDrawList _draw_list;

static DrawBuffer _buff1, _buff2;
static size_t _buff_active;

static DrawBuffer* _nt_draw_engine_get_active_buffer()
{
    if(_buff_active == 1) return &_buff1;
    else return &_buff2;
}

static DrawBuffer* _nt_draw_engine_get_inactive_buffer()
{
    if(_buff_active == 1) return &_buff2;
    else return &_buff1;
}

static void _nt_draw_engine_update_active_buffer_size()
{
    DrawBuffer* active_buffer = _nt_draw_engine_get_active_buffer();

    active_buffer->width = nt_display_get_display_width();
    active_buffer->height = nt_display_get_display_height();
}

static void _nt_draw_engine_switch_buffers()
{
    if(_buff_active == 1) _buff_active = 2;
    else _buff_active = 1;

    _nt_draw_engine_update_active_buffer_size();
}

// -------------------------------------------------------------------------------------------------------------

static void _nt_draw_engine_draw_window_to_active_buffer(struct NTWindow* window);
static void _nt_draw_engine_draw_active_buffer_to_screen(enum NTRootDrawOptimization draw_optimization);

// -------------------------------------------------------------------------------------------------------------

void nt_draw_engine_init()
{
    _nt_draw_buffer_init(&_buff1);
    _nt_draw_buffer_init(&_buff2);

    _buff_active = 1;
    _nt_draw_engine_update_active_buffer_size();

    _nt_draw_list_init(&_draw_list);
}

void nt_draw_engine_add_window_to_draw_queue(struct NTWindow* window)
{
    if(window->_draw_priority == NT_DRAW_ENGINE_HIGH_DRAW_PRIORITY) // if not background, draw at the end
        _nt_draw_list_push_back(&_draw_list, window);
    else // if background, draw now so it can be covered by the window
        _nt_draw_list_push_front(&_draw_list, window);
}

void nt_draw_engine_draw(enum NTRootDrawOptimization draw_optimization)
{
    struct NTWindow* curr_window;
    while((curr_window = _nt_draw_list_get_head(&_draw_list)) != NULL)
    {
        _nt_draw_engine_draw_window_to_active_buffer(curr_window);
        _nt_draw_list_pop_front(&_draw_list);
    }

    _nt_draw_engine_draw_active_buffer_to_screen(draw_optimization);
}

void nt_draw_engine_stop_draw()
{
    _nt_draw_engine_draw_active_buffer_to_screen(NT_ROOT_DRAW_UNOPTIMIZED);

    struct NTWindow* curr_window;

    volatile size_t i = 0;
    while((curr_window = _nt_draw_list_get_head(&_draw_list)) != NULL)
    {
        _nt_draw_list_pop_front(&_draw_list);
        ++i;
    }

    nt_log_log("%d\n", i);
}

// -------------------------------------------------------------------------------------------------------------

static void _nt_draw_engine_draw_window_to_active_buffer(struct NTWindow* window)
{
    struct NTObject* _window = (struct NTObject*)window;

    size_t abs_start_x = nt_object_calculate_abs_start_x(_window);
    size_t abs_start_y = nt_object_calculate_abs_start_y(_window);
    size_t window_height = nt_object_calculate_height(_window);
    size_t window_width = nt_object_calculate_width(_window);

    DrawBuffer* active_buffer = _nt_draw_engine_get_active_buffer();

    struct NTDisplayCell curr_display_cell;
    size_t window_i = 0;
    size_t abs_i = abs_start_y;
    size_t window_j;
    size_t abs_j;
    for(; window_i < window_height; ++window_i, ++abs_i)
    {
        window_j = 0;
        abs_j = abs_start_x;
        for(; window_j < window_width; ++window_j, ++abs_j)
        {
            curr_display_cell = nt_window_get_content_at(window, window_j, window_i);
            nt_display_cell_assign(&(active_buffer->buffer[abs_i][abs_j]), &curr_display_cell);
        }
    }
}

static void _nt_draw_engine_draw_active_buffer_to_screen(enum NTRootDrawOptimization draw_optimization)
{
    DrawBuffer* active_buffer = _nt_draw_engine_get_active_buffer();
    DrawBuffer* inactive_buffer = _nt_draw_engine_get_inactive_buffer();
    size_t width = active_buffer->width;
    size_t height = active_buffer->height;

    size_t i, j;
    struct NTDisplayCell* active_display_cell;
    struct NTDisplayCell* inactive_display_cell;
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            active_display_cell = &(active_buffer->buffer[i][j]);
            inactive_display_cell = &(inactive_buffer->buffer[i][j]);
            if((draw_optimization == NT_ROOT_DRAW_UNOPTIMIZED) ||
                    (!_nt_draw_buffer_is_in_bounds(inactive_buffer, j, i)) || 
                    (!nt_display_cell_are_equal(active_display_cell, inactive_display_cell)))
            {
                nt_cursor_abs_move_to_xy(j, i);
                nt_color_set_fg_color(active_display_cell->fg_color_code);
                nt_color_set_bg_color(active_display_cell->bg_color_code);
                putchar(active_display_cell->content);
            }
        }
    }

    _nt_draw_engine_switch_buffers();
}

void nt_draw_engine_on_display_size_change()
{
    _nt_draw_engine_update_active_buffer_size();
}

