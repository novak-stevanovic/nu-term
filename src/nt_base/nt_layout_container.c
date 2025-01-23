#include <assert.h>

#include "nt_base/nt_layout_container.h"
#include "nt_base/nt_layout_manager.h"

void nt_layout_container_init(struct NTLayoutContainer* layout_container,
        struct NTContainer* parent,
        struct NTLayoutManager* layout_manager)
{
    assert(layout_container != NULL);
    assert(layout_manager != NULL);

    nt_container_init((struct NTContainer*)layout_container,
            parent,
            _nt_layout_container_draw_content_func,
            _nt_layout_container_get_children_func);
}

struct NTLayoutManager* nt_layout_container_get_layout_manager(struct NTLayoutContainer* layout_container)
{
    assert(layout_container != NULL);

    return layout_container->_layout_manager;
}

struct Vector* _nt_layout_container_get_children_func(const struct NTObject* layout_container)
{
    assert(layout_container != NULL);

    struct NTLayoutManager* layout_manager = nt_layout_container_get_layout_manager((struct NTLayoutContainer*)layout_container);
    
    return nt_layout_manager_get_children(layout_manager);
}

void nt_layout_container_draw_content_func(struct NTObject* layout_container, struct NTObjectSizeConstraints* constraints)
{
    assert(layout_container != NULL);

    struct NTLayoutManager* layout_manager = nt_layout_container_get_layout_manager((struct NTLayoutContainer*)layout_container);

    nt_layout_manager_arrange(layout_manager, constraints);

}
