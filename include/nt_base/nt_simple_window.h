#ifndef NT_SIMPLE_WINDOW_H
#define NT_SIMPLE_WINDOW_H

#include "nt_base/nt_window.h"

struct NTSimpleWindow
{
    struct NTWindow _base;
};

void nt_simple_window_init(struct NTSimpleWindow* simple_window,
        struct NTDisplayCell (*window_get_content_at_func)(struct NTWindow* window, size_t x, size_t y),
        NTDrawEngineDrawPriority draw_priority);

#endif
