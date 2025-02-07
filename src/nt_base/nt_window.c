#include <assert.h>

#include "nt_base/nt_window.h"
#include "api/nt_vec_api.h"
#include "nt_base/nt_constraints.h"
#include "nt_core/nt_draw_engine.h"

static void _nt_window_set_engine_suggested_size(struct NTWindow* window, struct NTConstraints* constraints);

// --------------------------------------------------------------------------------------------------------------------------------

void nt_window_init(struct NTWindow* window,
        void (*calculate_required_size_func)(struct NTWindow*, size_t*, size_t*),
        void (*draw_window_func)(struct NTWindow*, size_t, size_t),
        void (*get_content_at_func)(struct NTWindow*, size_t, size_t, struct NTDisplayCell*),
        NTDrawEngineDrawPriority draw_priority)
{
    assert(window != NULL);
    assert(get_content_at_func != NULL);
    assert(draw_window_func != NULL);
    assert(calculate_required_size_func != NULL);

    nt_object_init((struct NTObject*)window, _nt_window_draw_content_func, _nt_window_get_children_func);

    window->_draw_window_func = draw_window_func;
    window->_get_content_at_func = get_content_at_func;
    window->_calculate_required_size_func = calculate_required_size_func;
    window->_draw_priority = draw_priority;
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

void _nt_window_draw_content_func(struct NTObject* window, struct NTConstraints* constraints)
{
    assert(window != NULL);
    assert(constraints != NULL);

    struct NTWindow* _window = (struct NTWindow*)window;

    _nt_window_set_engine_suggested_size(_window, constraints);

    assert(_window->_draw_window_func != NULL);

    _window->_draw_window_func(_window, constraints->used_x, constraints->used_y);

    nt_draw_engine_add_window_to_draw_queue(_window);
}

// --------------------------------------------------------------------------------------------------------------------------------

static void _nt_window_set_engine_suggested_size(struct NTWindow* window, struct NTConstraints* constraints)
{
    assert(window != NULL);
    assert(constraints != NULL);

    struct NTObject* _window = (struct NTObject*)window;

    size_t required_x, required_y;
    assert(window->_calculate_required_size_func != NULL);
    window->_calculate_required_size_func(window, &required_x, &required_y);

    constraints->used_x = nt_draw_engine_calculate_suggested_size(
            _window->_min_size_x, _window->_max_size_x, _window->_pref_size_x,
            constraints->_min_width, constraints->_max_width,
            required_x);

    constraints->used_y = nt_draw_engine_calculate_suggested_size(
            _window->_min_size_y, _window->_max_size_y, _window->_pref_size_y,
            constraints->_min_height, constraints->_max_height,
            required_y);

    // printf("%d %d %d %d\n", constraints->_min_width, constraints->_min_height, constraints->_max_width, constraints->_max_height);
    // printf("%d %d\n", _window->_pref_size_x, _window->_pref_size_y);
    // printf("%d %d\n", required_x, required_y);
    // printf("%d %d\n", constraints->used_x, constraints->used_y);
}
