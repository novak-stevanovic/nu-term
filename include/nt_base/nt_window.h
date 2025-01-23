#ifndef NT_WINDOW_H
#define NT_WINDOW_H

#include "nt_base/nt_object.h"

struct NTDisplayCell;
struct Vector;

struct NTWindow
{
    struct NTObject _base;

    struct NTDisplayCell (*_get_content_at_func)(struct NTWindow*, size_t, size_t);
};

void nt_window_init(struct NTWindow* window, 
        void (*_get_content_at_func)(struct NTWindow*, size_t, size_t, struct NTDisplayCell*));

// struct NTDisplayCell nt_window_get_content_at_func(struct NTWindow* window, size_t x, size_t y);
void _nt_window_get_children_func(const struct NTObject* window, struct Vector* vec_buff);

#endif
