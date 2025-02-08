#ifndef NT_CONTENT_WINDOW_H
#define NT_CONTENT_WINDOW_H

#include <assert.h>

#include "nt_base/nt_window.h"
#include "nt_shared/nt_content_matrix.h"
#include "nt_shared/nt_display_cell.h"

struct NTContentWindow
{
    struct NTWindow _base;
    struct NTContentMatrix _content;

    char content;
    size_t bg_color, fg_color;
};

void nt_content_window_init(struct NTContentWindow* content_window,
        void (*calculate_required_size_func)(struct NTWindow*, size_t*, size_t*),
        void (*draw_window_func)(struct NTWindow*, size_t, size_t));

void _nt_content_window_get_content_at_func(struct NTWindow* content_window, size_t x, size_t y, struct NTDisplayCell* display_cell_buff);
void nt_content_window_set_content_at(struct NTContentWindow* content_window, size_t x, size_t y, struct NTDisplayCell* display_cell_bp);

#endif
