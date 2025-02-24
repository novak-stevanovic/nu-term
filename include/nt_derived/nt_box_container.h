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


struct NTBoxDataObject;
struct NTBoxChildDataObject;

struct NTBoxContainer
{
    struct NTContainer _base;

    struct NTPaddingObject _padding;
    size_t _spacing;

    NTBoxContainerMainAxisAlignment _main_axis_alignment;
    NTBoxContainerSecondaryAxisAlignment _secondary_axis_alignment;

    // Finds the 
    void (*_box_container_calculate_next_child_constraints_func)(struct NTBoxContainer* box_container,
            struct NTConstraints* out_child_constraints, struct NTBoxDataObject* data_obj, 
            struct NTObject* child);

    void (*_box_container_init_child_data_obj_func)(struct NTBoxContainer* box_container, struct NTBoxChildDataObject* child_data_obj,
            size_t child_width, size_t child_height, struct NTBoxDataObject* data_obj,
            struct NTObject* child);

    void (*_box_container_align_child_func)(struct NTBoxContainer* box_container, struct NTBoxChildDataObject* child_data_obj, 
            struct NTBoxDataObject* data_obj, size_t box_container_content_width, size_t box_container_content_height);

};

void nt_box_container_init(struct NTBoxContainer* box_container,

    void (*box_container_calculate_next_child_constraints_func)(struct NTBoxContainer* box_container,
            struct NTConstraints* out_child_constraints, struct NTBoxDataObject* data_obj, 
            struct NTObject* child),

    void (*box_container_init_child_data_obj_func)(struct NTBoxContainer* box_container, struct NTBoxChildDataObject* child_data_obj,
            size_t child_width, size_t child_height, struct NTBoxDataObject* data_obj,
            struct NTObject* child),

    void (*box_container_align_child_func)(struct NTBoxContainer* box_container, struct NTBoxChildDataObject* child_data_obj, 
            struct NTBoxDataObject* data_obj, size_t box_container_content_width, size_t box_container_content_height));


void nt_box_container_add_child(struct NTBoxContainer* box_container, struct NTObject* child);

#endif
