#include <assert.h>

#include "nt_base/nt_window.h"
#include "api/nt_vec_api.h"
#include "nt_core/nt_draw_engine.h"

void nt_window_init(struct NTWindow* window,
        void (*calculate_required_size_func)(struct NTWindow*, size_t*, size_t*),
        void (*draw_window_func)(struct NTWindow*, size_t, size_t),
        void (*get_content_at_func)(struct NTWindow*, size_t, size_t, struct NTDisplayCell*))
{
    assert(window != NULL);
    assert(get_content_at_func != NULL);
    assert(draw_window_func != NULL);
    assert(calculate_required_size_func != NULL);

    nt_object_init((struct NTObject*)window, _nt_window_draw_content_func, _nt_window_get_children_func);

    window->_draw_window_func = draw_window_func;
    window->_get_content_at_func = get_content_at_func;
}

void nt_window_get_content_at(struct NTWindow* window, size_t x, size_t y, struct NTDisplayCell* display_cell_buff)
{
    assert(window != NULL);
    assert(window->_get_content_at_func != NULL);
    assert(display_cell_buff != NULL);

    window->_get_content_at_func(window, x, y, display_cell_buff);
}

void _nt_window_get_children_func(const struct NTObject* window, struct Vector* vec_buff)
{
    assert(window != NULL);
    assert(vec_buff != NULL);

    assert(nt_vec_api_vec_get_count(vec_buff) == 0);
}

void _nt_window_draw_content_func(struct NTObject* window, struct NTObjectSizeConstraints* constraints)
{
    assert(window != NULL);
    assert(constraints != NULL);

    //TODO
    size_t required_x, required_y;
    // fill(required_xy);
    size_t actual_x = 1, actual_y = 1;
    // fill(actual_xy);
    struct NTWindow* _window = (struct NTWindow*)window;
    assert(_window->_draw_window_func != NULL);

    _window->_draw_window_func(_window, actual_x, actual_y);

    constraints->used_x = actual_x;
    constraints->used_y = actual_y;
    nt_draw_engine_add_window_to_draw_queue(_window);
}
