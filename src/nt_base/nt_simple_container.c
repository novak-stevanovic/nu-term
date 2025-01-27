#include <assert.h>

#include "nt_base/nt_simple_container.h"
#include "api/nt_vec_api.h"

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
    simple_container->_children = nt_vec_api_vec_create(1, 1, 1, NULL);
}

void _nt_simple_container_get_children_func(const struct NTObject* simple_container, struct Vector* vec_buff)
{
    assert(simple_container != NULL);
    assert(vec_buff != NULL);
    
    // TODO
    //((struct NTSimpleContainer*)simple_container)->_children;
    assert(1 != 1);
}
