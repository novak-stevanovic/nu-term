#include <stdlib.h>

#include "nt_derived/nt_layout_managers/nt_border_layout_manager.h"

void nt_border_layout_manager_init(struct NTBorderLayoutManager* border_layout_manager, struct NTLayoutContainer* layout_container)
{
    nt_layout_manager_init((struct NTLayoutManager*)border_layout_manager,
            layout_container,
            _nt_border_layout_manager_arrange_func,
            _nt_border_layout_manager_get_children_func);
}

void _nt_border_layout_manager_arrange_func(struct NTLayoutManager* border_layout_maanger, struct NTObjectSizeConstraints* constraints)
{
    //TODO
}

struct Vector* _nt_border_layout_manager_get_children_func(const struct NTLayoutManager* layout_manager)
{
    //TODO
    return NULL;
}
