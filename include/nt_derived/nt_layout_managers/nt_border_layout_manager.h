#ifndef NT_BORDER_LAYOUT_MANAGER_H
#define NT_BORDER_LAYOUT_MANAGER_H

#include "nt_base/nt_layout_manager.h"

struct NTBorderLayoutManager
{
    struct NTLayoutManager _base;
};

void nt_border_layout_manager_init(struct NTBorderLayoutManager* border_layout_manager, struct NTLayoutContainer* layout_container);

void _nt_border_layout_manager_arrange_func(struct NTLayoutManager* border_layout_maanger, struct NTObjectSizeConstraints* constraints); 
struct Vector* _nt_border_layout_manager_get_children_func(const struct NTLayoutManager* layout_manager);

#endif
