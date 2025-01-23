#ifndef NT_CONTENT_WINDOW_H
#define NT_CONTENT_WINDOW_H

#include <assert.h>

#include "nt_base/nt_window.h"
#include "nt_shared/nt_display_cell.h"

struct NTContentWindow
{
    struct NTWindow _base;
};

void nt_content_window_init(struct NTContentWindow* content_window);

void _nt_content_window_get_content_at_func(struct NTWindow* content_window, size_t x, size_t y, struct NTDisplayCell* display_cell_buff);

#endif
