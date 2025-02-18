#ifndef NT_BOX_CONTAINER_H
#define NT_BOX_CONTAINER_H

#include "nt_base/nt_container.h"
#include "nt_shared/nt_padding_object.h"

struct NTBoxDataObject;
struct NTBoxChildDataObject;

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

    void (*_calculate_next_child_constraints_func)(struct NTBoxContainer* box_container,
        struct NTConstraints* next_child_constraints,
        struct NTBoxDataObject* data_obj);

    void (*_initialize_child_data_obj_func)(struct NTBoxContainer* box_container,
            struct NTBoxChildDataObject* child_data_obj,
            struct NTConstraints* child_constraints,
            struct NTBoxDataObject* data_obj,
            struct NTObject* child);

    void (*_align_child_func)(struct NTBoxContainer* box_container,
        struct NTBoxChildDataObject* child_data_object,
        struct NTBoxDataObject* data_object,
        size_t final_content_height, size_t final_content_width);
};

void nt_box_container_init(struct NTBoxContainer* box_container,

    void (*calculate_next_child_constraints_func)(struct NTBoxContainer* box_container,
        struct NTConstraints* next_child_constraints,
        struct NTBoxDataObject* data_obj),

    void (*initialize_child_data_obj_func)(struct NTBoxContainer* box_container,
            struct NTBoxChildDataObject* child_data_obj,
            struct NTConstraints* child_constraints,
            struct NTBoxDataObject* data_obj,
            struct NTObject* child),

    void (*align_child_func)(struct NTBoxContainer* box_container,
        struct NTBoxChildDataObject* child_data_object,
        struct NTBoxDataObject* data_object,
        size_t final_content_height, size_t final_content_width));

void nt_box_container_add_child(struct NTBoxContainer* box_container, struct NTObject* child);

#endif
