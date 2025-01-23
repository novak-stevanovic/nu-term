#include "nt_derived/nt_windows/nt_content_window.h"

void nt_content_window_init(struct NTContentWindow* content_window)
{
    assert(content_window != NULL);

    nt_window_init((struct NTWindow*)content_window, _nt_content_window_get_content_at_func);
}

void _nt_content_window_get_content_at_func(struct NTWindow* content_window, size_t x, size_t y, struct NTDisplayCell* display_cell_buff)
{
    // TODO
    assert(1 != 1);
}
