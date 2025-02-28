#ifndef NT_CONTAINER_CHILD_DATA_H
#define NT_CONTAINER_CHILD_DATA_H

#include "nt_base/nt_bounds.h"
#include <stddef.h>

typedef struct NTObject NTObject;

typedef struct NTContainerChildData
{
    NTObject* child;
    
    NTBounds bounds;
     
} NTContainerChildData;

void nt_container_child_data_init(NTContainerChildData* container_child_data, NTObject* child,
        NTBounds bounds);

#endif // NT_CONTAINER_CHILD_DATA_H
