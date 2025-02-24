#include "nt_derived/nt_box_container.h"
#include "nt_derived/_nt_box_container.h"
#include "nt_misc.h"

static struct NTBaseDrawDataObject* _object_draw_content_init(struct NTObject* box_container,
        struct NTConstraints* constraints);

static struct NTObject* _container_arrange_get_next_child_func(struct NTContainer* box_container,
        struct NTConstraints* constraints,
        struct NTBaseDrawDataObject* draw_data,
        struct NTConstraints* out_child_constraints);

static void _container_arrange_post_draw_child_func(struct NTContainer* box_container,
        struct NTObject* child,
        size_t child_width, size_t child_height, 
        struct NTBaseDrawDataObject* draw_data);

static void _container_arrange_conclude_func(struct NTContainer* box_container,
        struct NTBaseDrawDataObject* draw_data);

static void _container_draw_full_draw_func(struct NTContainer* box_container,
        struct NTBaseDrawDataObject* data_object);

static void _object_conclude_draw_func(struct NTObject* box_container,
        struct NTBaseDrawDataObject* data_object);

static void _nt_box_container_align_children(struct NTBoxContainer* box_container, NTBoxDataObject* data_obj,
        size_t final_content_width, size_t final_content_height);

// ---------------------------------------------------------------------------------------------

void nt_box_container_init(struct NTBoxContainer* box_container,

    void (*box_container_calculate_next_child_constraints_func)(struct NTBoxContainer* box_container,
            struct NTConstraints* out_child_constraints, struct NTBoxDataObject* data_obj, 
            struct NTObject* child),

    void (*box_container_init_child_data_obj_func)(struct NTBoxContainer* box_container, struct NTBoxChildDataObject* child_data_obj,
            size_t child_width, size_t child_height, struct NTBoxDataObject* data_obj,
            struct NTObject* child),

    void (*box_container_align_child_func)(struct NTBoxContainer* box_container, struct NTBoxChildDataObject* child_data_obj, 
            struct NTBoxDataObject* data_obj, size_t box_container_content_width, size_t box_container_content_height))
{
    struct NTContainer* _box_container = (struct NTContainer*)box_container;
    nt_container_init(_box_container, _object_draw_content_init,
            _container_arrange_get_next_child_func,
            _container_arrange_post_draw_child_func,
            _container_arrange_conclude_func,
            _container_draw_full_draw_func,
            _object_conclude_draw_func);

    box_container->_box_container_calculate_next_child_constraints_func =
        box_container_calculate_next_child_constraints_func;

    box_container->_box_container_align_child_func = box_container_align_child_func;
    box_container->_box_container_init_child_data_obj_func = box_container_init_child_data_obj_func;

    box_container->_main_axis_alignment = NT_BOX_CONTAINER_MAIN_AXIS_ALIGNMENT_START;
    box_container->_secondary_axis_alignment = NT_BOX_CONTAINER_SECONDARY_AXIS_ALIGNMENT_START;

    nt_padding_object_init(&box_container->_padding);
    box_container->_spacing = 0;
}

void nt_box_container_add_child(struct NTBoxContainer* box_container, struct NTObject* child)
{
    gds_vector_push_back(&((struct NTContainer*)box_container)->_children, &child);
    child->_parent = (struct NTContainer*)box_container;
}

// ---------------------------------------------------------------------------------------------

static struct NTBaseDrawDataObject* _object_draw_content_init(struct NTObject* box_container,
        struct NTConstraints* constraints)
{

    NTBoxDataObject* data_object = (NTBoxDataObject*)malloc(sizeof(NTBoxDataObject));
    struct NTBaseDrawDataObject* _data_object = (struct NTBaseDrawDataObject*)data_object;
    nt_object_base_draw_data_object_init(_data_object);

    struct NTBoxContainer* _box_container = (struct NTBoxContainer*)box_container;
    struct NTContainer* __box_container = (struct NTContainer*)box_container;

    GDSVector* children = nt_container_get_children(__box_container);
    size_t children_count = gds_vector_get_count(children);

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

    _data_object->used_x = 0;
    _data_object->used_y = 0;

    return _data_object;

}

static struct NTObject* _container_arrange_get_next_child_func(struct NTContainer* box_container,
        struct NTConstraints* constraints,
        struct NTBaseDrawDataObject* draw_data,
        struct NTConstraints* out_child_constraints)
{
    struct NTBoxContainer* _box_container = (struct NTBoxContainer*)box_container;
    NTBoxDataObject* data_obj = (NTBoxDataObject*)draw_data;

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

    _box_container->_box_container_calculate_next_child_constraints_func(_box_container, out_child_constraints,
            data_obj, next_child);

    return next_child;

}

static void _container_arrange_post_draw_child_func(struct NTContainer* box_container,
        struct NTObject* child,
        size_t child_width, size_t child_height, 
        struct NTBaseDrawDataObject* draw_data)
{
    struct NTBoxContainer* _box_container = (struct NTBoxContainer*)box_container;

    NTBoxDataObject* data_obj = (NTBoxDataObject*)draw_data;

    if(data_obj->drawn_children_array == NULL) return;

    GDSArray* drawn_children_data = data_obj->drawn_children_array;
    NTBoxChildDataObject child_data_obj;

    // Initialize child_data_obj based on box orientation, already drawn children, spacing, padding.. etc
    _box_container->_box_container_init_child_data_obj_func(_box_container, &child_data_obj,
            child_width, child_height, data_obj, child);

    // Append child_data_obj to drawn_children_data
    gds_array_push_back(drawn_children_data, &child_data_obj);

}

static void _container_arrange_conclude_func(struct NTContainer* box_container,
        struct NTBaseDrawDataObject* draw_data)
{
    struct NTBoxContainer* _box_container = (struct NTBoxContainer*)box_container;

    NTBoxDataObject* data_obj = (NTBoxDataObject*)draw_data;

    struct NTPaddingObject* padding_obj = &_box_container->_padding;
    size_t padding_width = padding_obj->west + padding_obj->east;
    size_t padding_height = padding_obj->north + padding_obj->south;

    size_t final_content_width = ((draw_data->used_x) < data_obj->content_constraints._min_width) ?
         data_obj->content_constraints._min_width : draw_data->used_x;

    size_t final_content_height = ((draw_data->used_y) < data_obj->content_constraints._min_height) ?
         data_obj->content_constraints._min_height : draw_data->used_y;

    // Perform the actual positioning of elements by adjusting start positions
    _nt_box_container_align_children(_box_container, data_obj, final_content_width, final_content_height);

    draw_data->used_x = final_content_width + padding_width;
    draw_data->used_y = final_content_height + padding_height;
}

static void _container_draw_full_draw_func(struct NTContainer* box_container,
        struct NTBaseDrawDataObject* data_object)
{
    NTBoxDataObject* data_obj = (NTBoxDataObject*)data_object;
    size_t children_count = gds_array_get_count(data_obj->drawn_children_array);

    size_t i;
    NTBoxChildDataObject* curr_child_data_obj;
    for(i = 0; i < children_count; i++)
    {
        curr_child_data_obj = gds_array_at(data_obj->drawn_children_array, i);

        nt_object_set_object_position_based_on_dimensions(curr_child_data_obj->child,
                curr_child_data_obj->base_start_x,
                curr_child_data_obj->base_start_y,
                curr_child_data_obj->used_x,
                curr_child_data_obj->used_y);

    }

}

static void _object_conclude_draw_func(struct NTObject* box_container,
        struct NTBaseDrawDataObject* data_object)
{
    NTBoxDataObject* data_obj = (NTBoxDataObject*)data_object;

    gds_array_destruct(data_obj->drawn_children_array);
    free(data_obj->drawn_children_array);
}

static void _nt_box_container_align_children(struct NTBoxContainer* box_container, NTBoxDataObject* data_obj,
        size_t final_content_width, size_t final_content_height)
{
    size_t i;
    NTBoxChildDataObject* curr_obj;

    GDSArray* drawn_children_data = data_obj->drawn_children_array;
    size_t drawn_children_count = gds_array_get_count(drawn_children_data);

    for(i = 0; i < drawn_children_count; i++)
    {
        curr_obj = gds_array_at(drawn_children_data, i);
        box_container->_box_container_align_child_func((struct NTBoxContainer*)box_container,
                curr_obj, data_obj, final_content_width, final_content_height);
    }

}
