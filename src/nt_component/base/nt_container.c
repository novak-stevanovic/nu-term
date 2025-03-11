#include "nt_component/base/nt_container.h"
#include "nt_shared/nt_shared.h"

#include "nt_component/base/nt_object.h"
#include "nt_shared/nt_container_child_data.h"

static nt_override void _object_arrange_content_func(NTObject* container);

static nt_override void _object_display_content_func(NTObject* container);

/* -------------------------------------------------------------------------- */

void nt_container_init(NTContainer* container, 

        nt_override void (*container_arrange_children_func)(
            NTContainer* container, struct NTContainerChildData *out_array), 

        nt_override void (*object_calculate_content_req_size_func)(
            const NTObject* object, size_t* out_width, size_t* out_height))

{
    nt_object_init((NTObject*)container,
            _object_arrange_content_func,
            _object_display_content_func,
            object_calculate_content_req_size_func);
}

/* -------------------------------------------------------------------------- */

static nt_override void _object_arrange_content_func(NTObject* container)
{
    NTContainer* _container = (NTContainer*)container;

    NTObjectVector* children = &_container->_children;
    size_t child_count = children->_count;

    struct NTContainerChildData* child_data =
        malloc(sizeof(struct NTContainerChildData) * child_count);

    _container->_container_arrange_children_func(_container, child_data);

    size_t i;
    struct NTContainerChildData* curr_child_data;
    for(i = 0; i < child_count; i++)
    {
        curr_child_data = &child_data[i];
        nt_object_set_bounds(curr_child_data->child,
                &curr_child_data->_child_bounds);
    }
}

static nt_override void _object_display_content_func(NTObject* container)
{
    NTContainer* _container = (NTContainer*)container;

    NTObjectVector* children = &_container->_children;
    size_t child_count = children->_count;

    size_t i;
    for(i = 0; i < child_count; i++)
        nt_object_display(children->_vector[i]);
}
