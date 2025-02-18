#ifndef _NT_BOX_CONTAINER_H_
#define _NT_BOX_CONTAINER_H_

#include "gds_array.h"
#include "nt_base/nt_constraints.h"

typedef struct NTBoxDataObject
{
    GDSArray* drawn_children_array;
    size_t fully_drawn_children_count;

    struct NTConstraints content_constraints; // excludes padding

} NTBoxDataObject;

typedef struct NTBoxChildDataObject
{
    struct NTObject* child;
    size_t base_start_x, base_start_y;
    size_t used_x, used_y;
} NTBoxChildDataObject;

// ----------------------------------------------------------------------------------------------------------------------------------


#endif
