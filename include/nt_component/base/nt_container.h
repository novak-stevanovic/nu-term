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
     *
     *
     * 'height' and 'width' parameters refer to the height and width
     * of the container's content(and by extension, its children). The
     * children must be positioned inside the rectangle:
     * 0 <= child_start_x <= child_end_x <= 'width'
     * 0 <= child_start_y <= child_end_y <= 'height'
     *
     * This function must handle the scenario where 'width' and 'height'
     * are equal to 0. */

    nt_abstract void (*_container_arrange_children_func)(NTContainer* container,
            struct NTContainerChildData *out_array, size_t width, size_t height);

} NTContainer;

void nt_container_init(NTContainer* container, 

        nt_override void (*container_arrange_children_func)(
            NTContainer* container, struct NTContainerChildData *out_array,
            size_t width, size_t height), 

        nt_override void (*object_calculate_content_req_size_func)(
            const NTObject* object, size_t* out_width, size_t* out_height));

#endif // _NT_CONTAINER_H_
