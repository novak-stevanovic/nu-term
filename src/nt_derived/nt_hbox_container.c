#include <assert.h>

#include "nt_derived/nt_hbox_container.h"
#include "gds_array.h"
#include "nt_base/nt_constraints.h"
#include "nt_misc.h"

// ----------------------------------------------------------------------------------------------------------------------------------

static void* _nt_hbox_container_draw_content_init_func(struct NTContainer* hbox_container, struct NTConstraints* constraints);

static struct NTObject* _nt_hbox_container_get_next_func(struct NTContainer* hbox_container, struct NTConstraints* constraints,
    struct NTConstraints* child_constraints, void* data);

static void _nt_hbox_container_post_draw_child_func(struct NTContainer* hbox_container, struct NTObject* child,
    struct NTConstraints* parent_constraints, struct NTConstraints* child_constraints, void* data);

static void _nt_hbox_container_conclude_draw_func(struct NTContainer* hbox_container, struct NTConstraints* parent_constraints, void* data);

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

typedef struct
{
    GDSArray* drawn_children_array;
    size_t fully_drawn_children_count;

    size_t children_min_width, children_max_width; // min and max width of children + spacing depending on paddding
    size_t children_min_height, children_max_height; // min and max height of children + spacing depending on paddding

    size_t tallest_child_height;
    size_t children_width; // excluding spacing, padding
} NTHBoxDataObject;

typedef struct
{
    struct NTObject* child;
    size_t base_start_x, base_start_y;
    size_t used_x, used_y;
} NTHBoxChildDataObject;

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

    data_object->children_min_width = (constraints->_min_width > padding_width) ? constraints->_min_width - padding_width : 0;
    data_object->children_max_width = (constraints->_max_width > padding_width) ? constraints->_max_width - padding_width : 0;

    data_object->children_min_height = (constraints->_min_height > padding_height) ? constraints->_min_height - padding_height : 0;
    data_object->children_max_height = (constraints->_max_height > padding_height) ? constraints->_max_height - padding_height : 0;

    data_object->children_width = 0;
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

    GDSVector* children = nt_container_get_children(hbox_container);
    size_t children_count = gds_vector_get_count(children);
    
    GDSArray* drawn_children_data = data_obj->drawn_children_array;
    size_t drawn_children_count = gds_array_get_count(drawn_children_data);

    size_t spacing = _hbox_container->_spacing;

    size_t total_spacing = nt_box_container_calculate_total_spacing(spacing, data_obj->fully_drawn_children_count);
    size_t total_used_width = total_spacing = data_obj->children_width; // excluding padding

    struct NTObject* next_child = (drawn_children_count == children_count) ? NULL : *(struct NTObject**)gds_vector_at(children, drawn_children_count);

    if(next_child == NULL) return NULL; // no more children to draw

    bool last_child = ((drawn_children_count + 1) == children_count);

    size_t min_height, min_width, max_height, max_width;
    if(last_child) // if last child, stretch it to fit parent constraints
    {
        min_width = (data_obj->children_min_width > (total_used_width + spacing)) ?
            data_obj->children_min_width - (total_used_width + spacing) : 0;

        min_height = (data_obj->children_min_height > data_obj->tallest_child_height) ? data_obj->children_min_height : 0;
    }
    else
    {
        min_width = 0;
        min_height = 0;
    }

    max_height = data_obj->children_max_height;
    max_width = (data_obj->children_max_width > (total_used_width + spacing)) ?
        data_obj->children_max_width - (total_used_width + spacing) : 0;

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

    size_t total_spacing = nt_box_container_calculate_total_spacing(spacing, data_obj->fully_drawn_children_count);
    size_t total_used_width = total_spacing + data_obj->children_width; // excluding padding

    // TODO put this in a func
    NTHBoxChildDataObject child_data_obj;
    child_data_obj.child = child;
    child_data_obj.used_x = child_constraints->_used_x;
    child_data_obj.used_y = child_constraints->_used_y;
    child_data_obj.base_start_x = total_used_width + spacing;
    child_data_obj.base_start_y = 0;

    if(nt_constraints_has_object_been_drawn(child_data_obj.used_x, child_data_obj.used_y))
        data_obj->fully_drawn_children_count++;

    gds_array_push_back(data_obj->drawn_children_array, &child_data_obj);

    data_obj->tallest_child_height = nt_misc_max(data_obj->tallest_child_height, child_data_obj.used_y);
    data_obj->children_width += child_data_obj.used_x;
}

static void _nt_hbox_container_conclude_draw_func(struct NTContainer* hbox_container, struct NTConstraints* parent_constraints, void* data)
{
    struct NTBoxContainer* _hbox_container = (struct NTBoxContainer*)hbox_container;
    struct NTHBoxContainer* __hbox_container = (struct NTHBoxContainer*)hbox_container;

    NTHBoxDataObject* data_obj = (NTHBoxDataObject*)data;

    GDSVector* children = nt_container_get_children(hbox_container);
    size_t children_count = gds_vector_get_count(children);

    GDSArray* drawn_children_data = data_obj->drawn_children_array;
    size_t drawn_children_count = gds_array_get_count(drawn_children_data);

    size_t spacing = _hbox_container->_spacing;

    size_t total_spacing = nt_box_container_calculate_total_spacing(spacing, data_obj->fully_drawn_children_count);
    size_t total_used_width = total_spacing + data_obj->children_width; // excluding padding

    struct NTPaddingObject* padding_obj = &_hbox_container->_padding;
    size_t padding_width = padding_obj->west + padding_obj->east;
    size_t padding_height = padding_obj->north + padding_obj->south;

    if((total_used_width + padding_width) < parent_constraints->_min_width)
        parent_constraints->_used_x = parent_constraints->_min_width;
    else
        parent_constraints->_used_x = total_used_width + padding_width;

    if((data_obj->tallest_child_height + padding_height) < parent_constraints->_min_height)
        parent_constraints->_used_y = parent_constraints->_min_height;
    else
        parent_constraints->_used_y = data_obj->tallest_child_height + padding_height;

    size_t i;
    NTHBoxChildDataObject* curr_obj;

    size_t fixed_start_x;
    size_t fixed_start_y;
    // TODO - optional?
    for(i = 0; i < drawn_children_count; i++)
    {
        curr_obj = gds_array_at(drawn_children_data, i);
        fixed_start_x = curr_obj->base_start_x + padding_obj->west;
        fixed_start_y = curr_obj->base_start_y + padding_obj->north;
        _nt_object_set_object_position_based_on_dimensions(curr_obj->child, fixed_start_x, fixed_start_y, curr_obj->used_x, curr_obj->used_y);
    }

    gds_array_destruct(data_obj->drawn_children_array);
    free(data);
}
