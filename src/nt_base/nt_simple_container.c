#include <assert.h>

#include "nt_base/nt_simple_container.h"
#include "lib/gends_vector.h"

void nt_simple_container_init(struct NTSimpleContainer* simple_container,
        struct NTContainer* parent,
        void (*draw_content_func)(struct NTObject*, struct NTObjectSizeConstraints*))
{
    assert(simple_container != NULL);

    nt_container_init((struct NTContainer*)simple_container,
            parent,
            draw_content_func,
            _nt_simple_container_get_children_func);

    //TODO
    simple_container->_children = vec_init(1, 1, sizeof(void*));
}

struct Vector* _nt_simple_container_get_children_func(const struct NTObject* simple_container)
{
    assert(simple_container != NULL);
    
    return ((struct NTSimpleContainer*)simple_container)->_children;
}
