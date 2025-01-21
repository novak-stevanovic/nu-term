#include <assert.h>

#include "nt_base/nt_container.h"

void nt_container_init(struct NTContainer* container,
        struct NTContainer* parent,
        void (*arrange_content_func)(struct NTObject*, struct NTObjectBounds* bounds),
        struct Vector* (*get_children_func)(const struct NTObject*),
        void (*post_set_size_func)(struct NTObject*))
{
    assert(container != NULL);
    assert(arrange_content_func != NULL);
    assert(get_children_func != NULL);

    nt_object_init((struct NTObject*)container, parent, arrange_content_func, get_children_func, post_set_size_func);
}
