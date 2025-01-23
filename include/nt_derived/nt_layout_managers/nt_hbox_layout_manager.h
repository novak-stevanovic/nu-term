#ifndef NT_HBOX_LAYOUT_MANAGER_H
#define NT_HBOX_LAYOUT_MANAGER_H

#include <stddef.h>

#include "nt_base/nt_layout_manager.h"

struct Vector;

struct NTHBoxLayoutManager
{
    struct NTLayoutManager _base;

    size_t _padding;
    size_t _spacing;
};

void nt_hbox_layout_manager_init(struct NTHBoxLayoutManager* hbox_layout_manager, struct NTLayoutContainer* layout_container);

void _nt_hbox_layout_manager_arrange_func(struct NTLayoutManager* hbox_layout_maanger, struct NTObjectSizeConstraints* constraints); 
struct Vector* _nt_hbox_layout_manager_get_children_func(const struct NTLayoutManager* layout_manager);

#endif
