#include <assert.h>

#include "nt_derived/nt_box_container.h"
#include "gds_array.h"
#include "nt_base/nt_constraints.h"
#include "nt_misc.h"
#include "nt_derived/_nt_box_container.h"

// ----------------------------------------------------------------------------------------------------------------------------------

static void* _nt_box_container_draw_content_init_func(struct NTContainer* box_container, struct NTConstraints* constraints);

static struct NTObject* _nt_box_container_get_next_func(struct NTContainer* box_container, struct NTConstraints* constraints,
    struct NTConstraints* child_constraints, void* data);

static void _nt_box_container_post_draw_child_func(struct NTContainer* box_container, struct NTObject* child,
    struct NTConstraints* parent_constraints, struct NTConstraints* child_constraints, void* data);

static void _nt_box_container_conclude_draw_func(struct NTContainer* box_container, struct NTConstraints* parent_constraints, void* data);

static void _nt_box_container_align_children(struct NTBoxContainer* box_container, NTBoxDataObject* data_obj,
        size_t final_content_height, size_t final_content_width);

// ----------------------------------------------------------------------------------------------------------------------------------

void nt_box_container_init(struct NTBoxContainer* box_container,

    void (*calculate_next_child_constraints_func)(struct NTBoxContainer* box_container,
        struct NTConstraints* next_child_constraints,
        struct NTBoxDataObject* data_obj),

    void (*_initialize_child_data_obj)(struct NTBoxContainer* box_container,
            struct NTBoxChildDataObject* child_data_obj,
            struct NTConstraints* child_constraints,
            struct NTBoxDataObject* data_obj,
            struct NTObject* child),

    void (*_nt_box_container_align_child)(struct NTBoxContainer* box_container,
        struct NTBoxChildDataObject* child_data_object,
        struct NTBoxDataObject* data_object,
        size_t final_content_height, size_t final_content_width))
{
    nt_container_init((struct NTContainer*)box_container,
            _nt_box_container_draw_content_init_func,
            _nt_box_container_get_next_func,
            _nt_box_container_post_draw_child_func,
            _nt_box_container_conclude_draw_func);
}

void nt_box_container_add_child(struct NTBoxContainer* box_container, struct NTObject* child)
{
    gds_vector_push_back(&((struct NTContainer*)box_container)->_children, &child);
    child->_parent = (struct NTContainer*)box_container;
}

static void* _nt_box_container_draw_content_init_func(struct NTContainer* box_container, struct NTConstraints* constraints)
{
    struct NTBoxContainer* _box_container = (struct NTBoxContainer*)box_container;

    GDSVector* children = nt_container_get_children(box_container);
    size_t children_count = gds_vector_get_count(children);

    NTBoxDataObject* data_object = (NTBoxDataObject*)malloc(sizeof(NTBoxDataObject));
    data_object->fully_drawn_children_count = 0;

    if(children_count == 0)
        data_object->drawn_children_array = NULL;
    else
        data_object->drawn_children_array = gds_array_create(children_count, sizeof(NTBoxChildDataObject));
    
    struct NTPaddingObject* padding_obj = &_box_container->_padding;
    size_t padding_width = padding_obj->west + padding_obj->east;
    size_t padding_height = padding_obj->north + padding_obj->south;

    size_t min_width = (constraints->_min_width > padding_width) ? constraints->_min_width - padding_width : 0;
    size_t min_height = (constraints->_min_height > padding_height) ? constraints->_min_height - padding_height : 0;

    size_t max_width = (constraints->_max_width > padding_width) ? constraints->_max_width - padding_width : 0;
    size_t max_height = (constraints->_max_height > padding_height) ? constraints->_max_height - padding_height : 0;

    nt_constraints_init(&data_object->content_constraints, min_width, min_height, max_width, max_height);

    data_object->content_constraints._used_x = 0;
    data_object->content_constraints._used_y = 0;

    return data_object;
}

static struct NTObject* _nt_box_container_get_next_func(struct NTContainer* box_container, struct NTConstraints* constraints,
    struct NTConstraints* child_constraints, void* data)
{
    struct NTBoxContainer* _box_container = (struct NTBoxContainer*)box_container;
    NTBoxDataObject* data_obj = (NTBoxDataObject*)data;

    if(data_obj->drawn_children_array == NULL) return NULL; // no children

    // now searching for the next child --------------------------------------

    GDSVector* children = nt_container_get_children(box_container);
    size_t children_count = gds_vector_get_count(children);
    
    GDSArray* drawn_children_data = data_obj->drawn_children_array;
    size_t drawn_children_count = gds_array_get_count(drawn_children_data);

    struct NTObject* next_child = (drawn_children_count == children_count) ? NULL : 
        *(struct NTObject**)gds_vector_at(children, drawn_children_count);

    if(next_child == NULL) return NULL; // no more children to draw

    // now computing the next_child's constraints -----------------------------

    _box_container->_calculate_next_child_constraints_func(_box_container, child_constraints, data_obj);

    return next_child;
}

static void _nt_box_container_post_draw_child_func(struct NTContainer* box_container, struct NTObject* child,
    struct NTConstraints* parent_constraints, struct NTConstraints* child_constraints, void* data)
{
    struct NTBoxContainer* _box_container = (struct NTBoxContainer*)box_container;

    NTBoxDataObject* data_obj = (NTBoxDataObject*)data;

    if(data_obj->drawn_children_array == NULL) return;

    GDSArray* drawn_children_data = data_obj->drawn_children_array;
    NTBoxChildDataObject child_data_obj;

    // Initialize child_data_obj based on box orientation, already drawn children, spacing, padding.. etc
    _box_container->_initialize_child_data_obj_func(_box_container, &child_data_obj, child_constraints, data_obj, child);

    // Append child_data_obj to drawn_children_data
    gds_array_push_back(drawn_children_data, &child_data_obj);

}

static void _nt_box_container_conclude_draw_func(struct NTContainer* box_container, struct NTConstraints* parent_constraints, void* data)
{
    struct NTBoxContainer* _box_container = (struct NTBoxContainer*)box_container;
    struct NTBoxContainer* __box_container = (struct NTBoxContainer*)box_container;
    struct NTObject* ___box_container = (struct NTObject*)box_container;

    NTBoxDataObject* data_obj = (NTBoxDataObject*)data;

    struct NTPaddingObject* padding_obj = &_box_container->_padding;
    size_t padding_width = padding_obj->west + padding_obj->east;
    size_t padding_height = padding_obj->north + padding_obj->south;

    struct NTConstraints* content_constraints = &data_obj->content_constraints;

    // take into account object min, max, pref sizes
    size_t final_container_height, final_container_width; 
    nt_draw_engine_calculate_suggested_size_obj(___box_container,
            parent_constraints,
            padding_width + content_constraints->_used_x,
            padding_height + content_constraints->_used_y, &final_container_width, &final_container_height);

    nt_constraints_set_values(parent_constraints, final_container_width, final_container_height);
    
    size_t final_content_width = final_container_width - padding_width;
    size_t final_content_height = final_container_height - padding_height;

    // Perform the actual positioning of elements by adjusting start positions
    _nt_box_container_align_children(__box_container, data, final_content_height, final_content_width);

    gds_array_destruct(data_obj->drawn_children_array);
    free(data);
}

static void _nt_box_container_align_children(struct NTBoxContainer* box_container, NTBoxDataObject* data_obj,
        size_t final_content_height, size_t final_content_width)
{
    size_t i;
    NTBoxChildDataObject* curr_obj;

    GDSArray* drawn_children_data = data_obj->drawn_children_array;
    size_t drawn_children_count = gds_array_get_count(drawn_children_data);

    for(i = 0; i < drawn_children_count; i++)
    {
        curr_obj = gds_array_at(drawn_children_data, i);
        box_container->_nt_box_container_align_child_func((struct NTBoxContainer*)box_container, curr_obj, data_obj, final_content_height, final_content_width);
    }

}

