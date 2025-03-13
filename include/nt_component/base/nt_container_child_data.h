#ifndef _NT_CONTAINER_CHILD_DATA_H_
#define _NT_CONTAINER_CHILD_DATA_H_

#include "nt_shared/nt_bounds.h"

struct NTObject;
typedef struct NTObject NTObject;

struct NTContainerChildData
{
    NTObject* child;
    NTBounds _child_bounds;
};

#endif
