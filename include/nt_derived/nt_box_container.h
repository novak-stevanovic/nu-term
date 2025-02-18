#ifndef NT_BOX_CONTAINER_H
#define NT_BOX_CONTAINER_H

#include "nt_base/nt_container.h"
#include "nt_shared/nt_padding_object.h"

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
    struct NTPaddingObject _padding;
    size_t _spacing;
    NTBoxContainerMainAxisAlignment _main_axis_alignment;
    NTBoxContainerSecondaryAxisAlignment _secondary_axis_alignment;
};

void nt_box_container_init(struct NTBoxContainer* box_container,

        void* (*draw_content_init_func)(struct NTContainer* box_container, struct NTConstraints* constraints),

        struct NTObject* (*get_next_func)(struct NTContainer* box_container, struct NTConstraints* constraints,
            struct NTConstraints* child_constraints, void* data),

        void (*post_draw_child_func)(struct NTContainer* box_container, struct NTObject* child,
            struct NTConstraints* parent_constraints, struct NTConstraints* child_constraints,
            void* data),

        void (*conclude_draw_func)(struct NTContainer* box_container, struct NTConstraints* parent_constraints, void* data));

size_t nt_box_container_calculate_total_spacing(size_t spacing, size_t drawn_children);

void nt_box_container_add_child(struct NTBoxContainer* box_container, struct NTObject* child);

#endif
