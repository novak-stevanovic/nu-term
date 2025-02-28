#include "nt_base/nt_container_child_data.h"

void nt_container_child_data_init(NTContainerChildData* container_child_data, NTObject* child,
        NTBounds bounds)
{
    container_child_data->child = child;
    container_child_data->bounds = bounds;
}
