#ifndef NT_WINDOW_H
#define NT_WINDOW_H

#include "nt_base/nt_object.h"

struct NTDisplayCell;
struct Vector;

struct NTWindow
{
    struct NTObject _base;

    void (*_get_content_at_func)(struct NTWindow*, size_t, size_t, struct NTDisplayCell*);
};

void nt_window_init(struct NTWindow* window,
        struct NTContainer* parent,
        void (*draw_content_func)(struct NTObject*, struct NTObjectSizeConstraints*),
        void (*get_content_at_func)(struct NTWindow*, size_t, size_t, struct NTDisplayCell*));

void nt_window_get_content_at(struct NTWindow* window, size_t x, size_t y, struct NTDisplayCell* display_cell_buff);

void _nt_window_get_children_func(const struct NTObject* window, struct Vector* vec_buff);

#endif
