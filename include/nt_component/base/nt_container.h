#ifndef _NT_CONTAINER_H_
#define _NT_CONTAINER_H_

#include "nt_component/base/nt_object.h"
#include "nt_util/nt_object_vector.h"

struct NTContainerChildData;

/* NTContainer(derived from NTObject) doesn't have its own content;
 * its sole purpose is to hold child objects (NTObjects) and manage
 * their layout. It is responsible for recalculating and updating
 * the positions of its children based on the available space,
 * ensuring that every child is correctly positioned. */
typedef struct NTContainer
{
    NTObject _base;
    NTObjectVector _children;

    /* This function must be overriden by any NTContainer concretizations.
     * It must recalculate the bounds for every child(start and end positions)
     * and fill the 'out_array' with such data. There must be exactly one entry
     * in the array, for each child. Children not drawn(due to any reason)
     * should have their bounds set to 0, 0, 0, 0. 
     * This data is then internally used by NTContainer to actually update the
     * positions of its children.
     * The NTContainer can infer the available space it has for positioning its
     * children based on its _bounds(from NTObject). It must handle the scenario
     * if the available width and/or height are 0. */
    nt_abstract void (*_container_arrange_children_func)(NTContainer* container,
            struct NTContainerChildData *out_array);

} NTContainer;

void nt_container_init(NTContainer* container, 

        nt_override void (*container_arrange_children_func)(
            NTContainer* container, struct NTContainerChildData *out_array), 

        nt_override void (*object_calculate_content_req_size_func)(
            const NTObject* object, size_t* out_width, size_t* out_height));

#endif // _NT_CONTAINER_H_
