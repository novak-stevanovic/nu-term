#include "nt_base/nt_content_window.h"
#include "nt_core/nt_draw_engine.h"
#include "nt_log.h"

#define _CONTENT_MATRIX_Y_MIN_COUNT 10
#define _CONTENT_MATRIX_Y_RESIZE_COUNT 5
#define _CONTENT_MATRIX_X_MIN_COUNT 50
#define _CONTENT_MATRIX_X_RESIZE_COUNT 10

void nt_content_window_init(struct NTContentWindow* content_window,
        void (*calculate_required_size_func)(struct NTWindow*, size_t*, size_t*),
        void (*draw_window_func)(struct NTWindow*, size_t, size_t))
{
    assert(content_window != NULL);
    assert(draw_window_func != NULL);
    assert(calculate_required_size_func != NULL);

    nt_window_init((struct NTWindow*)content_window, calculate_required_size_func, draw_window_func, _nt_content_window_get_content_at_func, NT_DRAW_ENGINE_HIGH_DRAW_PRIORITY);

    nt_content_matrix_init(&content_window->_content);
}

void _nt_content_window_get_content_at_func(struct NTWindow* content_window, size_t x, size_t y, struct NTDisplayCell* display_cell_buff)
{
    assert(content_window != NULL);
    assert(display_cell_buff != NULL);

    struct NTContentWindow* _content_window = (struct NTContentWindow*)content_window;
    struct NTDisplayCell* display_cell = (struct NTDisplayCell*)nt_content_matrix_at(&_content_window->_content, x, y);

    // nt_log_log("CELL WANTED AT: %ld %ld\n", x, y);

    // printf("%d\n", x);
    assert(display_cell != NULL);

    nt_display_cell_assign(display_cell_buff, display_cell);
}

void nt_content_window_set_content_at(struct NTContentWindow* content_window, size_t x, size_t y, struct NTDisplayCell* display_cell_bp)
{
    assert(content_window != NULL);
    assert(display_cell_bp != NULL);

    struct NTContentWindow* _content_window = (struct NTContentWindow*)content_window;
    struct NTDisplayCell* display_cell = (struct NTDisplayCell*)nt_content_matrix_at(&_content_window->_content, x, y);

    assert(display_cell != NULL);

    nt_display_cell_assign(display_cell, display_cell_bp);
}
