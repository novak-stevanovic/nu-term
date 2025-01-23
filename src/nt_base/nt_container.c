#include <assert.h>

#include "nt_base/nt_container.h"

void nt_container_init(struct NTContainer* container,
        struct NTContainer* parent,
        void (*draw_content_func)(struct NTObject*, struct NTObjectSizeConstraints* constraints),
        struct Vector* (*get_children_func)(const struct NTObject*))
{
    assert(container != NULL);
    assert(draw_content_func != NULL);
    assert(get_children_func != NULL);

    nt_object_init((struct NTObject*)container, parent, draw_content_func, get_children_func);
}
