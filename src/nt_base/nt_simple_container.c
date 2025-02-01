#include <assert.h>

#include "nt_base/nt_simple_container.h"
#include "api/nt_vec_api.h"

void nt_simple_container_init(struct NTSimpleContainer* simple_container,
        void (*draw_content_func)(struct NTObject*, struct NTObjectSizeConstraints*))
{
    assert(simple_container != NULL);

    nt_container_init((struct NTContainer*)simple_container,
            draw_content_func,
            _nt_simple_container_get_children_func);

    //TODO
    simple_container->_children = nt_vec_api_vec_create(1, 1, 1, NULL);
}

void _nt_simple_container_get_children_func(const struct NTObject* simple_container, struct Vector* vec_buff)
{
    assert(simple_container != NULL);
    assert(vec_buff != NULL);

    struct NTSimpleContainer* _simple_container = (struct NTSimpleContainer*)simple_container;

    size_t vec_buff_count = nt_vec_api_vec_get_count(vec_buff);
    struct Vector* children = _simple_container->_children;
    size_t child_count = nt_vec_api_vec_get_count(children);
    assert(vec_buff_count == 0);

    int i;
    for(i = 0; i < child_count; i++) assert(nt_vec_api_vec_append(vec_buff, nt_vec_api_vec_at(children, i)) == 0);
}
