#include "nt_base/nt_window.h"
#include "nt_core/_nt_draw_buffer.h"
#include "nt_core/_nt_draw_list.h"
#include "nt_core/nt_color.h"
#include "nt_core/nt_cursor.h"
#include "nt_core/nt_display.h"

// -----------------------------------------------------------------------------

static NTDrawBuffer _buff1, _buff2;
static size_t _active_buff = 0;

static NTDrawBuffer* _get_active_buffer()
{
    return (_active_buff == 1) ? &_buff1 : &_buff2;
}

static NTDrawBuffer* _get_inactive_buffer()
{
    return (_active_buff == 2) ? &_buff1 : &_buff2;
}

static void _set_active_draw_buffer_size()
{
    NTDrawBuffer* active_buffer = _get_active_buffer();

    active_buffer->height = nt_display_get_height();
    active_buffer->width = nt_display_get_width();
}

static void _switch_active_buffers()
{
    if(_active_buff == 0) _active_buff = 1;
    else if(_active_buff == 1) _active_buff = 2;
    else _active_buff = 1;

    _set_active_draw_buffer_size();
}

// -----------------------------------------------------------------------------

static void _draw_window_to_active_buffer(NTWindow* window);
static void _draw_active_buffer_to_screen();
static void _draw_all();

static inline void _draw_display_cell_at(NTDisplayCell* display_cell, size_t x, size_t y)
{
    nt_cursor_abs_move_to_xy(x, y);
    nt_color_set_bg_color(display_cell->bg_color_code);
    nt_color_set_fg_color(display_cell->fg_color_code);
    putchar(display_cell->content);
}

// -----------------------------------------------------------------------------

static NTDrawList _draw_list;

void nt_draw_engine_init()
{
    _nt_draw_list_init(&_draw_list);
    _nt_draw_buffer_init(&_buff1);
    _nt_draw_buffer_init(&_buff2);

    _switch_active_buffers();
}

void nt_draw_engine_add_to_draw_queue(NTWindow* window)
{
    if(nt_window_has_draw_priority_background(window))
        _nt_draw_list_push_front(&_draw_list, window);
    else
        _nt_draw_list_push_back(&_draw_list, window);
}

static void _draw_all()
{
    NTWindow* curr_window;
    while((curr_window = _nt_draw_list_get_head(&_draw_list)) != NULL)
    {
        _draw_window_to_active_buffer(curr_window);
        _nt_draw_list_pop_front(&_draw_list);
    }

    _draw_active_buffer_to_screen();
    _switch_active_buffers();
}

void nt_draw_engine_draw_object_tree(NTObject* object)
{
    nt_object_arrange(object);
    nt_object_display(object);
    _draw_all();
}

void nt_draw_engine_on_display_size_change()
{
    _set_active_draw_buffer_size();
}

static void _draw_window_to_active_buffer(NTWindow* window)
{
    NTObject* _window = (NTObject*)window;

    NTDrawBuffer* active_buffer = _get_active_buffer();

    size_t start_x = nt_object_calculate_abs_start_x(_window);
    size_t start_y = nt_object_calculate_abs_start_y(_window);

    const NTBounds* bounds = nt_object_get_bounds(_window);

    size_t width = nt_bounds_calculate_width(bounds);
    size_t height = nt_bounds_calculate_height(bounds);
    size_t i, j;

    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
            active_buffer->buffer[start_y + i][start_x + j] =
                nt_window_get_content_at(window, j, i); 
    }
}

static void _draw_active_buffer_to_screen()
{
    NTDrawBuffer* active_buffer = _get_active_buffer();

    size_t width = active_buffer->width;
    size_t height = active_buffer->height;

    size_t i, j;
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            _draw_display_cell_at(&active_buffer->buffer[i][j], j, i);
        }
    }
}
