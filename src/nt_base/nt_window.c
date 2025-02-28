#include "nt_base/nt_window.h"
#include "nt_core/nt_draw_engine.h"

static void _object_display_func(NTObject* window);

void nt_window_init(NTWindow* window, 

        void (*object_calculate_req_size_func)(const NTObject* window,
            size_t* out_width, size_t* out_height),

        void (*object_arrange_func)(NTObject* window),

        NTDisplayCell (*window_get_content_at_func)(const NTWindow* window,
            size_t x, size_t y))
{

    nt_object_init((NTObject*)window, object_calculate_req_size_func, object_arrange_func, _object_display_func);

    window->_window_get_content_at_func = window_get_content_at_func;
}

static void _object_display_func(NTObject* window)
{
    nt_draw_engine_add_to_draw_queue((NTWindow*)window);
}

NTDisplayCell nt_window_get_content_at(const NTWindow* window, size_t x, size_t y)
{
    return window->_window_get_content_at_func(window, x, y);
}

bool nt_window_has_draw_priority_background(const NTWindow* window)
{
    return (window->_draw_priority == NT_WINDOW_DRAW_PRIORITY_BACKGROUND);
}

void nt_window_change_draw_priority(NTWindow* window)
{
    if(window->_draw_priority == NT_WINDOW_DRAW_PRIORITY_REGULAR)
        window->_draw_priority = NT_WINDOW_DRAW_PRIORITY_BACKGROUND;
    else
        window->_draw_priority = NT_WINDOW_DRAW_PRIORITY_REGULAR;

}
