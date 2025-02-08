#ifndef NT_BOX_CONTAINER_H
#define NT_BOX_CONTAINER_H

#include "nt_base/nt_container.h"

typedef enum { NT_BOX_CONTAINER_ORIENTATION_HORIZONTAL, NT_BOX_CONTAINER_ORIENTATION_VERTICAL } NTBoxContainerOrientation;

typedef enum { 
    NT_BOX_CONTAINER_MAIN_AXIS_ALIGNMENT_START,
    NT_BOX_CONTAINER_MAIN_AXIS_ALIGNMENT_CENTER,
    NT_BOX_CONTAINER_MAIN_AXIS_ALIGNMENT_END } NTBoxContainerMainAxisAlignment;

typedef enum { 
    NT_BOX_CONTAINER_SECONDARY_AXIS_ALIGNMENT_START,
    NT_BOX_CONTAINER_SECONDARY_AXIS_ALIGNMENT_CENTER,
    NT_BOX_CONTAINER_SECONDARY_AXIS_ALIGNMENT_END } NTBoxContainerSecondaryAxisAlignment;

struct NTBoxContainer
{
    struct NTContainer _base;
    NTBoxContainerOrientation _orientation;
    NTBoxContainerMainAxisAlignment _main_axis_alignment;
    NTBoxContainerSecondaryAxisAlignment _secondary_axis_alignment;
};

void nt_box_container_init(struct NTBoxContainer* box_container, NTBoxContainerOrientation orientation);

#endif
