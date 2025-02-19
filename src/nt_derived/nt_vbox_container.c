// TODO - fix logic

#include "nt_derived/nt_vbox_container.h"
#include "nt_derived/_nt_box_container.h"
#include "gds_array.h"
#include "nt_misc.h"

// ----------------------------------------------------------------------------------------------------------------------------------

void _nt_vbox_calculate_next_child_constraints(struct NTBoxContainer* vbox_container,
    struct NTConstraints* next_child_constraints,
    struct NTBoxDataObject* data_obj);

void _nt_vbox_initialize_child_data_obj(struct NTBoxContainer* vbox_container,
    struct NTBoxChildDataObject* child_data_obj,
    struct NTConstraints* child_constraints,
    struct NTBoxDataObject* data_obj,
    struct NTObject* child);

void _nt_vbox_container_align_child(struct NTBoxContainer* vbox_container,
    struct NTBoxChildDataObject* child_data_object,
    struct NTBoxDataObject* data_obj,
    size_t final_content_height, size_t final_content_width);

// ----------------------------------------------------------------------------------------------------------------------------------

void nt_vbox_container_init(struct NTVBoxContainer* vbox_container)
{

    nt_box_container_init((struct NTBoxContainer*)vbox_container,
            _nt_vbox_calculate_next_child_constraints,
            _nt_vbox_initialize_child_data_obj,
            _nt_vbox_container_align_child);
}

void _nt_vbox_calculate_next_child_constraints(struct NTBoxContainer* vbox_container,
    struct NTConstraints* next_child_constraints,
    struct NTBoxDataObject* data_obj)
{
    struct NTBoxContainer* _vbox_container = (struct NTBoxContainer*)vbox_container;

    GDSArray* drawn_children_data = data_obj->drawn_children_array;
    size_t drawn_children_count = gds_array_get_count(drawn_children_data);

    bool first_child = (drawn_children_count == 0);

    size_t spacing = _vbox_container->_spacing;

    size_t min_height, min_width, max_height, max_width;

    min_width = 0;
    min_height = 0;

    struct NTConstraints* content_constraints = &data_obj->content_constraints;

    max_height = content_constraints->_max_height;

    if(first_child) // if first child, don't take into account the spacing left of it
    {
        max_width = (content_constraints->_max_width > content_constraints->_used_x) ?
            content_constraints->_max_width - content_constraints->_used_x : 0;
    }
    else
    {
        max_width = (content_constraints->_max_width > (content_constraints->_used_x + spacing)) ?
            content_constraints->_max_width - (content_constraints->_used_x + spacing) : 0;
    }

    nt_constraints_init(next_child_constraints, min_width, min_height, max_width, max_height);
}

void _nt_vbox_initialize_child_data_obj(struct NTBoxContainer* vbox_container,
    struct NTBoxChildDataObject* child_data_obj,
    struct NTConstraints* child_constraints,
    struct NTBoxDataObject* data_obj,
    struct NTObject* child)
{
    GDSArray* drawn_children_data = data_obj->drawn_children_array;
    size_t drawn_children_count = gds_array_get_count(drawn_children_data);

    size_t spacing = vbox_container->_spacing;

    child_data_obj->child = child;
    child_data_obj->used_x = child_constraints->_used_x;
    child_data_obj->used_y = child_constraints->_used_y;

    struct NTConstraints* content_constraints = &data_obj->content_constraints;

    if(nt_constraints_has_object_been_drawn_c(child_constraints))
    {
        bool first_child = (drawn_children_count == 0);

        if(first_child)  // if first child, don't take into account the spacing left of it
            child_data_obj->base_start_x = content_constraints->_used_x;
        else
            child_data_obj->base_start_x = content_constraints->_used_x + spacing;

        child_data_obj->base_start_y = 0;
    
        // update data object
        data_obj->fully_drawn_children_count++;
        content_constraints->_used_y = nt_misc_max(content_constraints->_used_y, child_data_obj->used_y);
        if(first_child) // if first child, no spacing left of the child was drawn
            content_constraints->_used_x += child_data_obj->used_x;
        else
            content_constraints->_used_x += child_data_obj->used_x + spacing;
    }
    else
    {
        child_data_obj->base_start_x = 0;
        child_data_obj->base_start_y = 0;
    }
}

void _nt_vbox_container_align_child(struct NTBoxContainer* vbox_container,
        NTBoxChildDataObject* child_data_object,
        NTBoxDataObject* data_object,
        size_t final_content_height, size_t final_content_width)
{
    struct NTBoxContainer* _vbox_container = (struct NTBoxContainer*)vbox_container;
    struct NTPaddingObject* padding = &_vbox_container->_padding;

    size_t offset_x, offset_y;

    struct NTConstraints* content_constraints = &data_object->content_constraints;

    // ADJUST X -------------------------------------------------------------------------------------------------

    if(_vbox_container->_main_axis_alignment == NT_BOX_CONTAINER_MAIN_AXIS_ALIGNMENT_START)
        offset_x = padding->west;

    else if(_vbox_container->_main_axis_alignment == NT_BOX_CONTAINER_MAIN_AXIS_ALIGNMENT_CENTER)
        offset_x = (final_content_width - content_constraints->_used_x) / 2 + padding->west;

    else // NT_BOX_CONTAINER_MAIN_AXIS_ALIGNMENT_END
        offset_x = final_content_width - content_constraints->_used_x + padding->west;

    // ADJUST Y -------------------------------------------------------------------------------------------------

    if(_vbox_container->_secondary_axis_alignment == NT_BOX_CONTAINER_SECONDARY_AXIS_ALIGNMENT_START)
        offset_y = padding->north;

    else if(_vbox_container->_secondary_axis_alignment == NT_BOX_CONTAINER_SECONDARY_AXIS_ALIGNMENT_CENTER)
        offset_y = (final_content_height - child_data_object->used_y) / 2 + padding->north;

    else // NT_BOX_CONTAINER_SECONDARY_AXIS_ALIGNMENT_END
        offset_y = final_content_height - child_data_object->used_y + padding->north;

    // ----------------------------------------------------------------------------------------------------------

    _nt_object_set_object_position_based_on_dimensions(child_data_object->child,
            child_data_object->base_start_x + offset_x,
            child_data_object->base_start_y + offset_y,
            child_data_object->used_x,
            child_data_object->used_y);
}

