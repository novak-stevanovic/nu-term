#include <stdlib.h>
#include <assert.h>

#include "nt_core/nt_draw_engine.h"
#include "nt_base/nt_object.h"
#include "nt_base/nt_window.h"
#include "nt_core/nt_color.h"
#include "nt_core/nt_cursor.h"
#include "nt_core/nt_display.h"
#include "nt_misc.h"
#include "nt_shared/nt_display_cell.h"

// ----------------------------------------------------------------------------------------------------------------------------

struct DrawItem
{
    struct NTWindow* window;
    struct DrawItem* next;
};

struct DrawList
{
    struct DrawItem *head, *tail;
};

struct DrawList draw_list;

// ----------------------------------------------------------------------------------------------------------------------------

static void _draw_list_init()
{
    draw_list.head = NULL;
    draw_list.head = NULL;
}

static struct DrawItem* _draw_item_create(struct NTWindow* window)
{
    assert(window != NULL);

    struct DrawItem* new = (struct DrawItem*)malloc(sizeof(struct DrawItem*));

    new->window = window;
    new->next = NULL;

    return new;
}

static void _draw_list_push_back(struct NTWindow* window)
{
    assert(window != NULL);
    struct DrawItem* new_item = _draw_item_create(window);

    if((draw_list.head == NULL) && (draw_list.tail == NULL))
    {
        draw_list.head = new_item;
        draw_list.tail = new_item;
    }
    else if((draw_list.head != NULL) && (draw_list.tail != NULL))
    {
        draw_list.tail->next = new_item;
        draw_list.tail = new_item;
    }
    else assert(1 != 1);
}

static void _draw_list_push_front(struct NTWindow* window)
{
    assert(window != NULL);
    struct DrawItem* new_item = _draw_item_create(window);

    if((draw_list.head == NULL) && (draw_list.tail == NULL))
    {
        draw_list.head = new_item;
        draw_list.tail = new_item;
    }
    else if((draw_list.head != NULL) && (draw_list.tail != NULL))
    {
        struct DrawItem* old_head = draw_list.head;
        draw_list.head = new_item;
        new_item->next = old_head;
    }
    else assert(1 != 1);
}

static void _draw_list_pop()
{
    if((draw_list.head != NULL) && (draw_list.tail != NULL))
    {
        struct DrawItem* next = draw_list.head->next;
        free(draw_list.head);
        draw_list.head = next;

        if(next == NULL) draw_list.tail = NULL;
    }
    else if((draw_list.head == NULL) && (draw_list.tail == NULL)) assert(1 != 1);
    else assert(1000 != 1000);
}

// ----------------------------------------------------------------------------------------------------------------------------

void _nt_draw_engine_draw_window(struct NTWindow* window);
void _nt_draw_engine_draw_display_cell(struct NTDisplayCell* display_cell, size_t abs_x, size_t abs_y);

// ----------------------------------------------------------------------------------------------------------------------------

void nt_draw_engine_init()
{
    _draw_list_init();
}

void nt_draw_engine_add_window_to_draw_queue(struct NTWindow* window)
{
    assert(window != NULL);

    (window->_draw_priority == NT_DRAW_ENGINE_HIGH_DRAW_PRIORITY) ? _draw_list_push_back(window) : _draw_list_push_front(window);
}

void nt_draw_engine_draw()
{
    while(draw_list.head != NULL)
    {
        _nt_draw_engine_draw_window(draw_list.head->window);
        _draw_list_pop();
    }
}

void _nt_draw_engine_draw_window(struct NTWindow* window)
{
    assert(window != NULL);

    struct NTObject* _window = (struct NTObject*)window;

    // printf("DRAWING WINDOW: %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld\n", 
    // _window->_rel_start_x, _window->_rel_start_y, _window->_rel_end_x, _window->_rel_end_y,
    // _window->_min_size_x, _window->_min_size_y,
    // _window->_pref_size_x, _window->_pref_size_y,
    // _window->_max_size_x, _window->_max_size_y);

    size_t abs_start_x = nt_object_calculate_abs_start_x(_window);
    size_t abs_start_y = nt_object_calculate_abs_start_y(_window);
    size_t window_height = nt_object_calculate_height(_window);
    size_t window_width = nt_object_calculate_width(_window);

    // printf("CALCU: %ld %ld %ld %ld\n", abs_start_x, abs_start_y, window_width, window_height);

   int i, j;
    struct NTDisplayCell display_cell_buff;
    for(i = 0; i < window_height; i++)
    {
        for(j = 0; j < window_width; j++)
        {
            nt_window_get_content_at(window, j, i, &display_cell_buff);
            _nt_draw_engine_draw_display_cell(&display_cell_buff, abs_start_x + j, abs_start_y + i);
        }
    }
}

int ita = 0;
void _nt_draw_engine_draw_display_cell(struct NTDisplayCell* display_cell, size_t x, size_t y)
{
    assert(display_cell != NULL);
    assert(x < nt_display_get_display_width());
    assert(y < nt_display_get_display_height());

    // printf("\t\t\t\t\t%d\n", ita++);

    size_t cursor_x = nt_cursor_get_abs_x();
    size_t cursor_y = nt_cursor_get_abs_y();

    int move_status = nt_cursor_abs_move_to_xy(x, y);
    assert(move_status == 0);

    ssize_t bg_color_code = display_cell->bg_color_code;
    ssize_t fg_color_code = display_cell->fg_color_code;
    char content = display_cell->content;

    if(bg_color_code != NT_COLOR_DEFAULT) nt_color_set_bg_color(bg_color_code);
    if(fg_color_code != NT_COLOR_DEFAULT) nt_color_set_fg_color(fg_color_code);
    // TODO putchar???
    if(content != 0) putchar(content);

    move_status = nt_cursor_abs_move_to_xy(cursor_x, cursor_y);
    assert(move_status == 0);
}

size_t nt_draw_engine_calculate_suggested_size(size_t obj_min_size, size_t obj_max_size, size_t obj_pref_size,
        size_t constraint_min_size, size_t constraint_max_size,
        size_t required_size)
{
    assert(obj_min_size <= obj_max_size);
    assert(constraint_min_size <= constraint_max_size);

    size_t min_size = (((constraint_min_size < obj_min_size) && (obj_min_size < constraint_max_size)) ? obj_min_size : constraint_min_size);
    size_t max_size = (((constraint_max_size > obj_max_size) && (obj_max_size > constraint_min_size)) ? obj_max_size : constraint_max_size);

    size_t ideal_size = ((obj_pref_size == NT_OBJECT_SIZE_UNSPECIFIED) ? obj_pref_size : required_size);

    return nt_misc_conform_val(min_size, ideal_size, max_size);
}

int nt_draw_engine_can_object_be_drawn(size_t min_width, size_t min_height, size_t max_width, size_t max_height)
{
    return !(((min_width == 0) && (max_width == 0)) || ((min_height == 0) && (max_height == 0)));
}
