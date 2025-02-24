#include "nt_derived/nt_hbox_container.h"
#include "gds_array.h"
#include "nt_derived/_nt_box_container.h"
#include "nt_misc.h"

static void _box_container_calculate_next_child_constraints_func(struct NTBoxContainer* hbox_container,
        struct NTConstraints* out_child_constraints, struct NTBoxDataObject* data_obj, 
        struct NTObject* child);

static void _box_container_init_child_data_obj_func(struct NTBoxContainer* hbox_container, struct NTBoxChildDataObject* child_data_obj,
        size_t child_width, size_t child_height, struct NTBoxDataObject* data_obj,
        struct NTObject* child);

static void _box_container_align_child_func(struct NTBoxContainer* hbox_container, struct NTBoxChildDataObject* child_data_obj, 
        struct NTBoxDataObject* data_obj, size_t box_container_content_width, size_t box_container_content_height);

void nt_hbox_container_init(struct NTHBoxContainer* hbox_container)
{
    nt_box_container_init((struct NTBoxContainer*)hbox_container, 
            _box_container_calculate_next_child_constraints_func,
            _box_container_init_child_data_obj_func,
            _box_container_align_child_func);
}


static void _box_container_calculate_next_child_constraints_func(struct NTBoxContainer* hbox_container,
        struct NTConstraints* out_child_constraints, struct NTBoxDataObject* data_obj, 
        struct NTObject* child)
{
    struct NTBoxContainer* _hbox_container = (struct NTBoxContainer*)hbox_container;
    struct NTBaseDrawDataObject* _data_obj = (struct NTBaseDrawDataObject*)data_obj;

    struct GDSArray* drawn_children_data = data_obj->drawn_children_array;
    size_t drawn_children_count = gds_array_get_count(drawn_children_data);

    bool first_child = (drawn_children_count == 0);

    size_t spacing = _hbox_container->_spacing;

    size_t min_height, min_width, max_height, max_width;

    min_width = 0;
    min_height = 0;

    struct NTConstraints* content_constraints = &data_obj->content_constraints;

    max_height = content_constraints->_max_height;

    if(first_child) // if first child, don't take into account the spacing left of it
    {
        max_width = (content_constraints->_max_width > _data_obj->used_x) ?
            content_constraints->_max_width - _data_obj->used_x : 0;
    }
    else
    {
        max_width = (content_constraints->_max_width > (_data_obj->used_x + spacing)) ?
            content_constraints->_max_width - (_data_obj->used_x + spacing) : 0;
    }

    nt_constraints_init(out_child_constraints, min_width, min_height, max_width, max_height);

}

static void _box_container_init_child_data_obj_func(struct NTBoxContainer* hbox_container, struct NTBoxChildDataObject* child_data_obj,
        size_t child_width, size_t child_height, struct NTBoxDataObject* data_obj,
        struct NTObject* child)
{
    struct NTBaseDrawDataObject* _data_obj = (struct NTBaseDrawDataObject*)data_obj;
    GDSArray* drawn_children_data = data_obj->drawn_children_array;
    size_t drawn_children_count = gds_array_get_count(drawn_children_data);

    size_t spacing = hbox_container->_spacing;

    child_data_obj->child = child;
    child_data_obj->used_x = child_width;
    child_data_obj->used_y = child_height;

    if((child_height != 0) && (child_width != 0))
    {
        bool first_child = (drawn_children_count == 0);

        if(first_child)  // if first child, don't take into account the spacing left of it
            child_data_obj->base_start_x = _data_obj->used_x;
        else
            child_data_obj->base_start_x = _data_obj->used_x + spacing;

        child_data_obj->base_start_y = 0;
    
        // update data object
        data_obj->fully_drawn_children_count++;
        _data_obj->used_y = nt_misc_max(_data_obj->used_y, child_data_obj->used_y);
        if(first_child) // if first child, no spacing left of the child was drawn
            _data_obj->used_x += child_data_obj->used_x;
        else
            _data_obj->used_x += child_data_obj->used_x + spacing;
    }
    else
    {
        child_data_obj->base_start_x = 0;
        child_data_obj->base_start_y = 0;
    }

}

static void _box_container_align_child_func(struct NTBoxContainer* hbox_container, struct NTBoxChildDataObject* child_data_obj, 
        struct NTBoxDataObject* data_obj, size_t box_container_content_width, size_t box_container_content_height)
{
    struct NTBaseDrawDataObject* _data_obj = (struct NTBaseDrawDataObject*)data_obj;
    struct NTBoxContainer* _hbox_container = (struct NTBoxContainer*)hbox_container;
    struct NTPaddingObject* padding = &_hbox_container->_padding;

    size_t offset_x, offset_y;

    // ADJUST X -------------------------------------------------------------------------------------------------

    if(_hbox_container->_main_axis_alignment == NT_BOX_CONTAINER_MAIN_AXIS_ALIGNMENT_START)
        offset_x = padding->west;

    else if(_hbox_container->_main_axis_alignment == NT_BOX_CONTAINER_MAIN_AXIS_ALIGNMENT_CENTER)
        offset_x = (box_container_content_width - _data_obj->used_x) / 2 + padding->west;

    else // NT_BOX_CONTAINER_MAIN_AXIS_ALIGNMENT_END
        offset_x = box_container_content_width - _data_obj->used_x + padding->west;

    // ADJUST Y -------------------------------------------------------------------------------------------------

    if(_hbox_container->_secondary_axis_alignment == NT_BOX_CONTAINER_SECONDARY_AXIS_ALIGNMENT_START)
        offset_y = padding->north;

    else if(_hbox_container->_secondary_axis_alignment == NT_BOX_CONTAINER_SECONDARY_AXIS_ALIGNMENT_CENTER)
        offset_y = (box_container_content_height - child_data_obj->used_y) / 2 + padding->north;

    else // NT_BOX_CONTAINER_SECONDARY_AXIS_ALIGNMENT_END
        offset_y = box_container_content_height - child_data_obj->used_y + padding->north;

    // ----------------------------------------------------------------------------------------------------------

    child_data_obj->base_start_x += offset_x;
    child_data_obj->base_start_y += offset_y;
}

