#include <assert.h>

#include "nt_base/nt_layout_container.h"
#include "nt_base/nt_layout_manager.h"

void nt_layout_container_init(struct NTLayoutContainer* layout_container,
        struct NTLayoutManager* layout_manager)
{
    assert(layout_container != NULL);
    assert(layout_manager != NULL);

    nt_container_init((struct NTContainer*)layout_container,
            _nt_layout_container_arrange_content_func,
            _nt_layout_container_get_children_func);

    layout_container->_layout_manager = layout_manager;
}

struct NTLayoutManager* nt_layout_container_get_layout_manager(struct NTLayoutContainer* layout_container)
{
    assert(layout_container != NULL);

    return layout_container->_layout_manager;
}

void _nt_layout_container_arrange_content_func(struct NTContainer* layout_container, struct NTConstraints* constraints)
{
    assert(layout_container != NULL);
    assert(constraints != NULL);

    struct NTLayoutManager* layout_manager = nt_layout_container_get_layout_manager((struct NTLayoutContainer*)layout_container);

    nt_layout_manager_arrange(layout_manager, constraints);
}

void _nt_layout_container_get_children_func(const struct NTObject* layout_container, struct Vector* vec_buff)
{
    assert(layout_container != NULL);

    struct NTLayoutManager* layout_manager = nt_layout_container_get_layout_manager((struct NTLayoutContainer*)layout_container);
    
    nt_layout_manager_get_children(layout_manager, vec_buff);
}
