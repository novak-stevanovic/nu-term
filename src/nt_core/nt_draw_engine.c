#include <stdlib.h>

#include "nt_core/nt_draw_engine.h"
#include "nt_base/nt_constraints.h"
#include "nt_base/nt_object.h"
#include "nt_base/nt_window.h"
#include "nt_core/nt_color.h"
#include "nt_core/nt_cursor.h"
#include "nt_core/nt_display.h"
#include "nt_log.h"
#include "nt_misc.h"
#include "nt_shared/nt_content_matrix.h"
#include "nt_shared/nt_display_cell.h"
#include "nt_core/_nt_draw_list.h"

typedef struct DrawBuffer
{
    struct NTDisplayCell buffer[250][250];
    size_t width, height;
} DrawBuffer;

static DrawBuffer _buff1, _buff2;
static size_t _buff_active;

// ----------------------------------------------------------------------------------------------------------------------------

static DrawBuffer* _nt_draw_engine_get_active_buffer();
static DrawBuffer* _nt_draw_engine_get_inactive_buffer();
static void _nt_draw_engine_switch_active_buffers();

void _nt_draw_engine_draw_window_to_buff(struct NTWindow* window);
void _nt_draw_engine_draw_display_cell_to_active_buff(struct NTDisplayCell* display_cell, size_t abs_x, size_t abs_y);
void _nt_draw_engine_draw_buff_to_screen();

// ----------------------------------------------------------------------------------------------------------------------------

void nt_draw_engine_init()
{
    _draw_list_init();

    _buff_active = 1;

    nt_draw_engine_update_active_buff_size();
}

void nt_draw_engine_add_window_to_draw_queue(struct NTWindow* window)
{
    (window->_draw_priority == NT_DRAW_ENGINE_HIGH_DRAW_PRIORITY) ? _draw_list_push_back(window) : _draw_list_push_front(window);
}

void nt_draw_engine_draw()
{
    while(draw_list.head != NULL)
    {
        _nt_draw_engine_draw_window_to_buff(draw_list.head->window);
        _draw_list_pop();
    }

    _nt_draw_engine_draw_buff_to_screen();
}

void _nt_draw_engine_draw_window_to_buff(struct NTWindow* window)
{
    struct NTObject* _window = (struct NTObject*)window;
    if(!_nt_object_is_object_drawn(_window)) return;

    size_t abs_start_x = nt_object_calculate_abs_start_x(_window);
    size_t abs_start_y = nt_object_calculate_abs_start_y(_window);
    size_t window_height = nt_object_calculate_height(_window);
    size_t window_width = nt_object_calculate_width(_window);

    int i, j;
    struct NTDisplayCell display_cell_buff;
    for(i = 0; i < window_height; i++)
    {
        for(j = 0; j < window_width; j++)
        {
            nt_window_get_content_at(window, j, i, &display_cell_buff);
            _nt_draw_engine_draw_display_cell_to_active_buff(&display_cell_buff, abs_start_x + j, abs_start_y + i);
        }
    }
}

void _nt_draw_engine_draw_display_cell_to_active_buff(struct NTDisplayCell* display_cell, size_t x, size_t y)
{
    DrawBuffer* active_buff = _nt_draw_engine_get_active_buffer();

    if(display_cell->content != 0)
    {
        nt_display_cell_assign(&active_buff->buffer[y][x], display_cell);
    }
}

void _nt_draw_engine_draw_buff_to_screen()
{
    DrawBuffer* inactive_buff = _nt_draw_engine_get_inactive_buffer();
    DrawBuffer* active_buff = _nt_draw_engine_get_active_buffer();

    int i, j;
    struct NTDisplayCell* active_display_cell, *inactive_display_cell = NULL;
    for(i = 0; i < active_buff->height; i++)
    {
        for(j = 0; j < active_buff->width; j++)
        {
            active_display_cell = &active_buff->buffer[i][j];

            if((i < inactive_buff->height) && (j < inactive_buff->width))
                inactive_display_cell = &inactive_buff->buffer[i][j];
            else
                inactive_display_cell = NULL;

            if((inactive_display_cell == NULL) || (!nt_display_cell_are_equal(active_display_cell, inactive_display_cell)))
            {
                nt_cursor_abs_move_to_xy(j, i);
                nt_color_set_bg_color(active_display_cell->bg_color_code);
                nt_color_set_fg_color(active_display_cell->fg_color_code);
                // TODO putchar???
                putchar(active_display_cell->content);
            }

        }
    }

    _nt_draw_engine_switch_active_buffers();

}

size_t nt_draw_engine_calculate_suggested_size(size_t obj_min_size, size_t obj_max_size, size_t obj_pref_size,
        size_t constraint_min_size, size_t constraint_max_size,
        size_t required_size)
{

    size_t min_size = (((constraint_min_size < obj_min_size) && (obj_min_size < constraint_max_size)) ? obj_min_size : constraint_min_size);
    size_t max_size = (((constraint_max_size > obj_max_size) && (obj_max_size > constraint_min_size)) ? obj_max_size : constraint_max_size);

    size_t ideal_size = ((obj_pref_size != NT_OBJECT_SIZE_UNSPECIFIED) ? obj_pref_size : required_size);

    return nt_misc_conform_val(min_size, ideal_size, max_size);
}

void nt_draw_engine_calculate_suggested_size_obj(struct NTObject* object,
        struct NTConstraints* constraints, size_t required_width, size_t required_height, size_t* out_width, size_t* out_height)
{
    size_t width = nt_draw_engine_calculate_suggested_size(object->_min_size_x, object->_max_size_x, object->_pref_size_x,
            constraints->_min_width, constraints->_max_width, required_width);

    size_t height = nt_draw_engine_calculate_suggested_size(object->_min_size_y, object->_max_size_y, object->_pref_size_y,
            constraints->_min_height, constraints->_max_height, required_height);

    if((width == 0) || (height == 0))
    {
        height = 0;
        width = 0;
    }

    *out_width = width;
    *out_height = height;
}

int nt_draw_engine_can_object_be_drawn(size_t min_width, size_t min_height, size_t max_width, size_t max_height)
{
    return !(((min_width == 0) && (max_width == 0)) || ((min_height == 0) && (max_height == 0)));
}

static DrawBuffer* _nt_draw_engine_get_active_buffer()
{
    if(_buff_active == 1) return &_buff1;
    else return &_buff2;
}

static DrawBuffer* _nt_draw_engine_get_inactive_buffer()
{
    if(_buff_active == 2) return &_buff1;
    else return &_buff2;
}

static void _nt_draw_engine_switch_active_buffers()
{
    _buff_active = (_buff_active + 1) % 2 + 1;

    nt_draw_engine_update_active_buff_size();
}

void nt_draw_engine_update_active_buff_size()
{
    DrawBuffer* active_buff = _nt_draw_engine_get_active_buffer();

    active_buff->height = nt_display_get_display_height();
    active_buff->width = nt_display_get_display_width();
}
