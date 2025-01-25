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
};

void nt_content_window_init(struct NTContentWindow* content_window,
        struct NTContainer* parent,
        void (*draw_content_func)(struct NTObject*, struct NTObjectSizeConstraints*));

void _nt_content_window_get_content_at_func(struct NTWindow* content_window, size_t x, size_t y, struct NTDisplayCell* display_cell_buff);
void nt_content_window_set_content_at(struct NTContentWindow* content_window, size_t x, size_t y, struct NTDisplayCell* display_cell_bp);

#endif
