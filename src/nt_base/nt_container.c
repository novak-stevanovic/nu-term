#include <assert.h>

#include "nt_base/nt_container.h"

void nt_container_init(struct NTContainer* container,
        struct NTContainer* parent,
        void (*draw_func)(struct NTObject*, void*),
        struct Vector* (*get_children_func)(struct NTObject*))
{
    assert(container != NULL);
    assert(draw_func != NULL);
    assert(get_children_func != NULL);

    nt_object_init((struct NTObject*)container, parent, draw_func, get_children_func);
}
