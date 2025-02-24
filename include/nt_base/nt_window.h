#ifndef NT_WINDOW_H
#define NT_WINDOW_H

#include "nt_base/nt_object.h"
#include "nt_core/nt_draw_engine.h"

struct NTWindow
{
    struct NTObject _base;

    // PART OF OBJECT_DRAW_FULL_DRAW_FUNC
    void (*_window_draw_full_draw_func)(struct NTWindow* window,
            struct NTBaseDrawDataObject* data_object);

    struct NTDisplayCell (*_window_get_content_at_func)(struct NTWindow* window, size_t x, size_t y);
    // NON-NULL

    NTDrawEngineDrawPriority _draw_priority;
};

void nt_window_init(struct NTWindow* window,

    struct NTBaseDrawDataObject* (*object_draw_init_func)(struct NTObject* window, struct NTConstraints* constraints),

    void (*object_draw_arrange_func)(struct NTObject* window,
            struct NTBaseDrawDataObject* data_object, struct NTConstraints* constraints, enum NTDrawMode draw_mode),
    
    void (*window_draw_full_draw_func)(struct NTWindow* window,
            struct NTBaseDrawDataObject* data_object),

    void (*object_draw_conclude_func)(struct NTObject* window,
            struct NTBaseDrawDataObject* data_object),

    struct NTDisplayCell (*window_get_content_at_func)(struct NTWindow* window,
        size_t x, size_t y),

    NTDrawEngineDrawPriority draw_priority);

struct NTDisplayCell nt_window_get_content_at(struct NTWindow* window, size_t x, size_t y);

#endif
