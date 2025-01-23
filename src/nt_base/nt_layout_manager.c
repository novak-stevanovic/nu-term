#include <stdlib.h>
#include <assert.h>

#include "nt_base/nt_layout_manager.h"

void nt_layout_manager_init(struct NTLayoutManager* layout_manager,
        struct NTLayoutContainer* layout_container,
        void (*arrange_func)(struct NTLayoutManager*, struct NTObjectSizeConstraints*),
        struct Vector* (*get_children_func)(const struct NTLayoutManager*))
{
    assert(layout_manager != NULL);
    assert(layout_container != NULL);
    assert(arrange_func != NULL);
    assert(get_children_func != NULL);

    layout_manager->_layout_container = layout_container;
    layout_manager->_arrange_func = arrange_func;
    layout_manager->_get_children_func = get_children_func;
}

void nt_layout_manager_arrange(struct NTLayoutManager* layout_manager, struct NTObjectSizeConstraints* constraints)
{
    assert(layout_manager != NULL);

    layout_manager->_arrange_func(layout_manager, NULL);
}

struct Vector* nt_layout_manager_get_children(const struct NTLayoutManager* layout_manager)
{
    assert(layout_manager != NULL);

    return layout_manager->_get_children_func(layout_manager);
}
