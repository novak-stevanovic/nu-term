#ifndef NT_WINDOW_H
#define NT_WINDOW_H

#include "nt_base/nt_object.h"
#include "nt_core/nt_draw_engine.h"

struct NTDisplayCell;
struct Vector;

struct NTWindow
{
    struct NTObject _base;

    void (*_calculate_required_size_func)(struct NTWindow*, size_t*, size_t*);
    void (*_get_content_at_func)(struct NTWindow*, size_t, size_t, struct NTDisplayCell*);
    void (*_draw_window_func)(struct NTWindow*, size_t, size_t);

    NTDrawEngineDrawPriority _draw_priority; // set priority to NT_DRAW_ENGINE_LOW_DRAW_PRIORITY for drawing windows that are overwritten by
                                             // later drawings of other windows
};

void nt_window_init(struct NTWindow* window,
        void (*calculate_required_size_func)(struct NTWindow*, size_t*, size_t*),
        void (*draw_window_func)(struct NTWindow*, size_t, size_t),
        void (*get_content_at_func)(struct NTWindow*, size_t, size_t, struct NTDisplayCell*),
        NTDrawEngineDrawPriority draw_priority);

void nt_window_get_content_at(struct NTWindow* window, size_t x, size_t y, struct NTDisplayCell* display_cell_buff);

void _nt_window_get_children_func(const struct NTObject* window, struct Vector* vec_buff);
void _nt_window_draw_content_func(struct NTObject* window, struct NTConstraints* constraints);

#endif
