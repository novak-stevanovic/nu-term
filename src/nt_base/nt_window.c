#include "nt_base/nt_window.h"
#include "nt_core/nt_draw_engine.h"
#include "nt_shared/nt_display_cell.h"

static void _nt_window_draw_full_draw_func(struct NTObject* window, 
        struct NTBaseDrawDataObject* data_object);

// ----------------------------------------------------------------------------------------------------------------

void nt_window_init(struct NTWindow* window,

    struct NTBaseDrawDataObject* (*object_draw_init_func)(struct NTObject* window,
        struct NTConstraints* constraints),

    void (*object_draw_arrange_func)(struct NTObject* window,
            struct NTBaseDrawDataObject* data_object, struct NTConstraints* constraints,
            enum NTDrawMode draw_mode),
    
    void (*window_draw_full_draw_func)(struct NTWindow* window,
            struct NTBaseDrawDataObject* data_object),

    void (*object_draw_conclude_func)(struct NTObject* window,
            struct NTBaseDrawDataObject* data_object),

    struct NTDisplayCell (*window_get_content_at_func)(struct NTWindow* window, size_t x, size_t y),

    NTDrawEngineDrawPriority draw_priority)
{
    nt_object_init((struct NTObject*)window, object_draw_init_func, object_draw_arrange_func,
            _nt_window_draw_full_draw_func, object_draw_conclude_func);

    window->_window_draw_full_draw_func = window_draw_full_draw_func;
    window->_window_get_content_at_func = window_get_content_at_func;
    window->_draw_priority = draw_priority;
}

static void _nt_window_draw_full_draw_func(struct NTObject* window,
        struct NTBaseDrawDataObject* data_object)
{
    struct NTWindow* _window = (struct NTWindow*)window;

    if(_window->_window_draw_full_draw_func != NULL) 
        _window->_window_draw_full_draw_func(_window, data_object);

    nt_draw_engine_add_window_to_draw_queue(_window);
}

struct NTDisplayCell nt_window_get_content_at(struct NTWindow* window, size_t x, size_t y)
{
    return window->_window_get_content_at_func(window, x, y);
}
