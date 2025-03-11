#ifndef _NT_CONTAINER_H_
#define _NT_CONTAINER_H_

#include "nt_component/base/nt_object.h"
#include "nt_shared/nt_object_vector.h"

struct NTContainerChildData;

typedef struct NTContainer
{
    NTObject _base;
    NTObjectVector _children;

    nt_abstract void (*_container_arrange_children_func)(NTContainer* container,
            struct NTContainerChildData *out_array);

} NTContainer;

void nt_container_init(NTContainer* container, 

        nt_override void (*container_arrange_children_func)(
            NTContainer* container, struct NTContainerChildData *out_array), 

        nt_override void (*object_calculate_content_req_size_func)(
            const NTObject* object, size_t* out_width, size_t* out_height));

#endif // _NT_CONTAINER_H_
