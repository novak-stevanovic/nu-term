#include <stdlib.h>
#include <assert.h>

#include "nt_base/nt_layout_manager.h"

void nt_layout_manager_init(struct NTLayoutManager* layout_manager,
        struct NTLayoutContainer* layout_container,
        void (*arrange_func)(struct NTLayoutManager*, struct NTConstraints*),
        void (*get_children_func)(const struct NTLayoutManager*, struct Vector*))
{
    assert(layout_manager != NULL);
    assert(layout_container != NULL);
    assert(arrange_func != NULL);
    assert(get_children_func != NULL);

    layout_manager->_layout_container = layout_container;
    layout_manager->_arrange_func = arrange_func;
    layout_manager->_get_children_func = get_children_func;
}

void nt_layout_manager_arrange(struct NTLayoutManager* layout_manager, struct NTConstraints* constraints)
{
    assert(layout_manager != NULL);
    assert(constraints != NULL);
    assert(layout_manager->_arrange_func != NULL);

    layout_manager->_arrange_func(layout_manager, constraints);
}

void nt_layout_manager_get_children(const struct NTLayoutManager* layout_manager, struct Vector* vec_buff)
{
    assert(layout_manager != NULL);

    layout_manager->_get_children_func(layout_manager, vec_buff);
}

struct NTLayoutContainer* nt_layout_manager_get_layout_container(struct NTLayoutManager* layout_manager)
{
    assert(layout_manager != NULL);

    return layout_manager->_layout_container;
}
