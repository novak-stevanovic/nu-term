#include <assert.h>

#include "nt_derived/nt_hbox_container.h"
#include "gds_array.h"
#include "nt_base/nt_constraints.h"
#include "nt_misc.h"

// ----------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
    GDSArray* drawn_children_array;
    size_t fully_drawn_children_count;

    size_t content_min_width, content_max_width; // min and max width of children + spacing depending on paddding
    size_t content_min_height, content_max_height; // min and max height of children + spacing depending on paddding

    size_t tallest_child_height;
    size_t used_width; // excluding spacing, padding
} NTHBoxDataObject;

typedef struct
{
    struct NTObject* child;
    size_t base_start_x, base_start_y;
    size_t used_x, used_y;
} NTHBoxChildDataObject;

// ----------------------------------------------------------------------------------------------------------------------------------

static void* _nt_hbox_container_draw_content_init_func(struct NTContainer* hbox_container, struct NTConstraints* constraints);

static struct NTObject* _nt_hbox_container_get_next_func(struct NTContainer* hbox_container, struct NTConstraints* constraints,
    struct NTConstraints* child_constraints, void* data);

static void _nt_hbox_container_post_draw_child_func(struct NTContainer* hbox_container, struct NTObject* child,
    struct NTConstraints* parent_constraints, struct NTConstraints* child_constraints, void* data);

static void _nt_hbox_container_conclude_draw_func(struct NTContainer* hbox_container, struct NTConstraints* parent_constraints, void* data);

static void _nt_hbox_container_align_children(struct NTHBoxContainer* hbox_container, NTHBoxDataObject* data_obj,
        size_t final_content_height, size_t final_content_width);

static void _nt_hbox_container_align_child(struct NTHBoxContainer* hbox_container,
        NTHBoxChildDataObject* child_data_object,
        NTHBoxDataObject* data_object,
        size_t final_content_height, size_t final_content_width);

// ----------------------------------------------------------------------------------------------------------------------------------

void nt_hbox_container_init(struct NTHBoxContainer* hbox_container)
{
    assert(hbox_container != NULL);

    nt_box_container_init((struct NTBoxContainer*)hbox_container,
            _nt_hbox_container_draw_content_init_func,
            _nt_hbox_container_get_next_func,
            _nt_hbox_container_post_draw_child_func,
            _nt_hbox_container_conclude_draw_func);
}

static void* _nt_hbox_container_draw_content_init_func(struct NTContainer* hbox_container, struct NTConstraints* constraints)
{
    struct NTBoxContainer* _hbox_container = (struct NTBoxContainer*)hbox_container;

    GDSVector* children = nt_container_get_children(hbox_container);
    size_t children_count = gds_vector_get_count(children);

    NTHBoxDataObject* data_object = (NTHBoxDataObject*)malloc(sizeof(NTHBoxDataObject));
    data_object->fully_drawn_children_count = 0;

    if(children_count == 0)
        data_object->drawn_children_array = NULL;
    else
        data_object->drawn_children_array = gds_array_create(children_count, sizeof(NTHBoxChildDataObject));
    
    struct NTPaddingObject* padding_obj = &_hbox_container->_padding;
    size_t padding_width = padding_obj->west + padding_obj->east;
    size_t padding_height = padding_obj->north + padding_obj->south;

    data_object->content_min_width = (constraints->_min_width > padding_width) ? constraints->_min_width - padding_width : 0;
    data_object->content_max_width = (constraints->_max_width > padding_width) ? constraints->_max_width - padding_width : 0;

    data_object->content_min_height = (constraints->_min_height > padding_height) ? constraints->_min_height - padding_height : 0;
    data_object->content_max_height = (constraints->_max_height > padding_height) ? constraints->_max_height - padding_height : 0;

    if(((data_object->content_min_width == 0) && (data_object->content_max_width == 0)) ||
    ((data_object->content_min_height == 0) && (data_object->content_max_height == 0)))
    {
        data_object->content_min_width = 0;
        data_object->content_max_width = 0;
        data_object->content_min_height = 0;
        data_object->content_max_height = 0;
    }

    data_object->used_width = 0;
    data_object->tallest_child_height = 0;

    return data_object;
}

static struct NTObject* _nt_hbox_container_get_next_func(struct NTContainer* hbox_container, struct NTConstraints* constraints,
    struct NTConstraints* child_constraints, void* data)
{
    struct NTBoxContainer* _hbox_container = (struct NTBoxContainer*)hbox_container;
    struct NTHBoxContainer* __hbox_container = (struct NTHBoxContainer*)hbox_container;
    NTHBoxDataObject* data_obj = (NTHBoxDataObject*)data;

    if(data_obj->drawn_children_array == NULL) return NULL; // no children

    // now searching for the next child --------------------------------------

    GDSVector* children = nt_container_get_children(hbox_container);
    size_t children_count = gds_vector_get_count(children);
    
    GDSArray* drawn_children_data = data_obj->drawn_children_array;
    size_t drawn_children_count = gds_array_get_count(drawn_children_data);

    struct NTObject* next_child = (drawn_children_count == children_count) ? NULL : *(struct NTObject**)gds_vector_at(children, drawn_children_count);

    if(next_child == NULL) return NULL; // no more children to draw

    // now computing the next_child's constraints -----------------------------

    bool first_child = (drawn_children_count == 0);

    size_t spacing = _hbox_container->_spacing;

    size_t min_height, min_width, max_height, max_width;

    min_width = 0;
    min_height = 0;

    max_height = data_obj->content_max_height;

    if(first_child) // if first child, don't take into account the spacing left of it
    {
        max_width = (data_obj->content_max_width > data_obj->used_width) ?
            data_obj->content_max_width - data_obj->used_width : 0;
    }
    else
    {
        max_width = (data_obj->content_max_width > (data_obj->used_width + spacing)) ?
            data_obj->content_max_width - (data_obj->used_width + spacing) : 0;
    }

    nt_constraints_init(child_constraints, min_width, min_height, max_width, max_height);

    return next_child;
}

static void _nt_hbox_container_post_draw_child_func(struct NTContainer* hbox_container, struct NTObject* child,
    struct NTConstraints* parent_constraints, struct NTConstraints* child_constraints, void* data)
{
    struct NTBoxContainer* _hbox_container = (struct NTBoxContainer*)hbox_container;
    struct NTHBoxContainer* __hbox_container = (struct NTHBoxContainer*)hbox_container;

    NTHBoxDataObject* data_obj = (NTHBoxDataObject*)data;

    if(data_obj->drawn_children_array == NULL) return;

    GDSVector* children = nt_container_get_children(hbox_container);
    size_t children_count = gds_vector_get_count(children);
    
    GDSArray* drawn_children_data = data_obj->drawn_children_array;
    size_t drawn_children_count = gds_array_get_count(drawn_children_data);

    size_t spacing = _hbox_container->_spacing;

    // TODO put this in a func
    NTHBoxChildDataObject child_data_obj;
    child_data_obj.child = child;
    child_data_obj.used_x = child_constraints->_used_x;
    child_data_obj.used_y = child_constraints->_used_y;


    if(nt_constraints_has_object_been_drawn_c(child_constraints))
    {
        bool first_child = (drawn_children_count == 0);

        if(first_child)  // if first child, don't take into account the spacing left of it
            child_data_obj.base_start_x = data_obj->used_width;
        else
            child_data_obj.base_start_x = data_obj->used_width + spacing;

        child_data_obj.base_start_y = 0;
    
        // update data object
        data_obj->fully_drawn_children_count++;
        data_obj->tallest_child_height = nt_misc_max(data_obj->tallest_child_height, child_data_obj.used_y);
        if(first_child) // if first child, no spacing left of the child was drawn
            data_obj->used_width += child_data_obj.used_x;
        else
            data_obj->used_width += child_data_obj.used_x + spacing;
    }
    else
    {
        child_data_obj.base_start_x = 0;
        child_data_obj.base_start_y = 0;
    }

    gds_array_push_back(data_obj->drawn_children_array, &child_data_obj);

}

static void _nt_hbox_container_conclude_draw_func(struct NTContainer* hbox_container, struct NTConstraints* parent_constraints, void* data)
{
    struct NTBoxContainer* _hbox_container = (struct NTBoxContainer*)hbox_container;
    struct NTHBoxContainer* __hbox_container = (struct NTHBoxContainer*)hbox_container;
    struct NTObject* ___hbox_container = (struct NTObject*)hbox_container;

    NTHBoxDataObject* data_obj = (NTHBoxDataObject*)data;

    GDSVector* children = nt_container_get_children(hbox_container);
    size_t children_count = gds_vector_get_count(children);

    GDSArray* drawn_children_data = data_obj->drawn_children_array;
    size_t drawn_children_count = gds_array_get_count(drawn_children_data);

    size_t spacing = _hbox_container->_spacing;

    struct NTPaddingObject* padding_obj = &_hbox_container->_padding;
    size_t padding_width = padding_obj->west + padding_obj->east;
    size_t padding_height = padding_obj->north + padding_obj->south;


    size_t used_x = nt_draw_engine_calculate_suggested_size(___hbox_container->_min_size_x,
            ___hbox_container->_max_size_x,
            ___hbox_container->_pref_size_x,
            parent_constraints->_min_width,
            parent_constraints->_max_width,
            data_obj->used_width + padding_width);

    size_t used_y = nt_draw_engine_calculate_suggested_size(___hbox_container->_min_size_y,
            ___hbox_container->_max_size_y,
            ___hbox_container->_pref_size_y,
            parent_constraints->_min_height,
            parent_constraints->_max_height,
            data_obj->tallest_child_height + padding_height);

    nt_constraints_set_values(parent_constraints, used_x, used_y);
    
    size_t final_content_width = parent_constraints->_used_x - padding_width;
    size_t final_content_height = parent_constraints->_used_y - padding_height;

    // Perform the actual positioning of elements by adjusting start positions
    _nt_hbox_container_align_children(__hbox_container, data, final_content_height, final_content_width);

    gds_array_destruct(data_obj->drawn_children_array);
    free(data);
}

static void _nt_hbox_container_align_children(struct NTHBoxContainer* hbox_container, NTHBoxDataObject* data_obj,
        size_t final_content_height, size_t final_content_width)
{
    struct NTContainer* _hbox_container = (struct NTContainer*)hbox_container;
    struct NTBoxContainer* __hbox_container = (struct NTBoxContainer*)hbox_container;

    size_t i;
    NTHBoxChildDataObject* curr_obj;

    GDSArray* drawn_children_data = data_obj->drawn_children_array;
    size_t drawn_children_count = gds_array_get_count(drawn_children_data);

    for(i = 0; i < drawn_children_count; i++)
    {
        curr_obj = gds_array_at(drawn_children_data, i);
        _nt_hbox_container_align_child(hbox_container, curr_obj, data_obj, final_content_height, final_content_width);
    }

}

static void _nt_hbox_container_align_child(struct NTHBoxContainer* hbox_container,
        NTHBoxChildDataObject* child_data_object,
        NTHBoxDataObject* data_object,
        size_t final_content_height, size_t final_content_width)
{
    struct NTBoxContainer* _hbox_container = (struct NTBoxContainer*)hbox_container;
    struct NTPaddingObject* padding = &_hbox_container->_padding;

    size_t offset_x, offset_y;

    // ADJUST X

    if(_hbox_container->_main_axis_alignment == NT_BOX_CONTAINER_MAIN_AXIS_ALIGNMENT_START)
    {
        offset_x = padding->west;
    }

    else if(_hbox_container->_main_axis_alignment == NT_BOX_CONTAINER_MAIN_AXIS_ALIGNMENT_CENTER)
    {
        offset_x = (final_content_width - data_object->used_width) / 2 + padding->west;
    }

    else // NT_BOX_CONTAINER_MAIN_AXIS_ALIGNMENT_END
    {
        offset_x = final_content_width - data_object->used_width + padding->west;
    }

    // ADJUST Y

    if(_hbox_container->_secondary_axis_alignment == NT_BOX_CONTAINER_SECONDARY_AXIS_ALIGNMENT_START)
    {
        offset_y = padding->north;
    }

    else if(_hbox_container->_secondary_axis_alignment == NT_BOX_CONTAINER_SECONDARY_AXIS_ALIGNMENT_CENTER)
    {
        offset_y = (final_content_height - child_data_object->used_y) / 2 + padding->north;
    }

    else // NT_BOX_CONTAINER_SECONDARY_AXIS_ALIGNMENT_END
    {
        offset_y = final_content_height - child_data_object->used_y + padding->north;
    }

    _nt_object_set_object_position_based_on_dimensions(child_data_object->child,
            child_data_object->base_start_x + offset_x,
            child_data_object->base_start_y + offset_y,
            child_data_object->used_x,
            child_data_object->used_y);
}

