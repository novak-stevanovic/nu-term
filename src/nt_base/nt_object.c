
#include "nt_base/nt_object.h"
#include "nt_base/nt_constraints.h"
#include "nt_log.h"
#include "nt_misc.h"

void nt_object_init(struct NTObject* object,

    struct NTBaseDrawDataObject* (*object_draw_init_func)(struct NTObject* object, struct NTConstraints* constraints),

    void (*object_draw_arrange_func)(struct NTObject* object,
            struct NTBaseDrawDataObject* data_object, struct NTConstraints* constraints, enum NTDrawMode draw_mode),
    
    void (*object_draw_full_draw_func)(struct NTObject* object,
            struct NTBaseDrawDataObject* data_object),

    void (*object_draw_conclude_func)(struct NTObject* object,
            struct NTBaseDrawDataObject* data_object))
{

    object->_object_draw_init_func = object_draw_init_func;
    object->_object_draw_arrange_func = object_draw_arrange_func;
    object->_object_draw_full_draw_func = object_draw_full_draw_func;
    object->_object_draw_conclude_func = object_draw_conclude_func;

    object->_pref_width = NT_OBJECT_PREF_SIZE_UNSPECIFIED;
    object->_pref_height = NT_OBJECT_PREF_SIZE_UNSPECIFIED;
    object->_min_width = NT_OBJECT_MIN_SIZE_UNSPECIFIED;
    object->_min_height = NT_OBJECT_MIN_SIZE_UNSPECIFIED;
    object->_max_width = NT_OBJECT_MAX_SIZE_UNSPECIFIED;
    object->_max_height = NT_OBJECT_MAX_SIZE_UNSPECIFIED;
    object->_rel_start_x = 0;
    object->_rel_start_y = 0;
    object->_rel_end_x = 0;
    object->_rel_end_y = 0;

    object->_parent = NULL;
}

void nt_object_draw(struct NTObject* obj,
        struct NTConstraints* constraints,
        enum NTDrawMode draw_mode,
        size_t* out_width, size_t* out_height)
{
    nt_constraints_apply_object_restrictions(constraints, obj);

    struct NTBaseDrawDataObject* data_object = (obj->_object_draw_init_func != NULL ) ?
        obj->_object_draw_init_func(obj, constraints) : NULL;

    obj->_object_draw_arrange_func(obj, data_object, constraints, draw_mode); 
    // returns width and height used based on constraints into info

    if((data_object->used_x == 0) || (data_object->used_y == 0))
    {
        data_object->used_x = 0;
        data_object->used_y= 0;
    }

    if(draw_mode == NT_DRAW_MODE_DRAW)
        obj->_object_draw_full_draw_func(obj, data_object);

    if(obj->_object_draw_conclude_func) obj->_object_draw_conclude_func(obj, data_object); 

    *out_width = data_object->used_x;
    *out_height = data_object->used_y;

    if(data_object != NULL) free(data_object);

}

void nt_object_base_draw_data_object_init(struct NTBaseDrawDataObject* data_object)
{
    data_object->used_x = 0;
    data_object->used_y = 0;
}

struct NTBaseDrawDataObject* nt_object_base_draw_data_object_create()
{
    struct NTBaseDrawDataObject* data_object = malloc(sizeof(struct NTBaseDrawDataObject));

    nt_object_base_draw_data_object_init(data_object);

    return data_object;
}


size_t nt_object_calculate_abs_start_x(const struct NTObject* obj)
{

    ssize_t coordinate_sum = 0;

    const struct NTObject* curr_obj = obj;
    const struct NTContainer* curr_parent;
    while(curr_obj != NULL)
    {
        curr_parent = nt_object_get_parent(curr_obj);
        coordinate_sum += nt_object_get_start_x(curr_obj);
        curr_obj = (const struct NTObject*)curr_parent;
    }

    return coordinate_sum;
}

size_t nt_object_calculate_abs_start_y(const struct NTObject* obj)
{

    ssize_t coordinate_sum = 0;

    const struct NTObject* curr_obj = obj;
    const struct NTContainer* curr_parent;
    while(curr_obj != NULL)
    {
        curr_parent = nt_object_get_parent(curr_obj);
        coordinate_sum += nt_object_get_start_y(curr_obj);
        curr_obj = (struct NTObject*)curr_parent;
    }

    return coordinate_sum;
}

size_t nt_object_calculate_abs_end_x(const struct NTObject* obj)
{

    return nt_object_calculate_abs_start_x(obj) + nt_object_get_end_x(obj) - nt_object_get_start_x(obj);
}

size_t nt_object_calculate_abs_end_y(const struct NTObject* obj)
{

    return nt_object_calculate_abs_start_y(obj) + nt_object_get_end_y(obj) - nt_object_get_start_y(obj);
}

size_t nt_object_calculate_height(const struct NTObject* obj)
{
    return obj->_rel_end_y - obj->_rel_start_y;
}

size_t nt_object_calculate_width(const struct NTObject* obj)
{

    return obj->_rel_end_x - obj->_rel_start_x;
}

size_t nt_object_get_start_x(const struct NTObject* obj)
{

    return obj->_rel_start_x;
}

size_t nt_object_get_start_y(const struct NTObject* obj)
{

    return obj->_rel_start_y;
}

size_t nt_object_get_end_x(const struct NTObject* obj)
{

    return obj->_rel_end_x;
}

size_t nt_object_get_end_y(const struct NTObject* obj)
{

    return obj->_rel_end_y;
}

ssize_t nt_object_get_pref_size_x(const struct NTObject* obj)
{

    return obj->_pref_width;
}

ssize_t nt_object_get_pref_size_y(const struct NTObject* obj)
{

    return obj->_pref_height;
}

ssize_t nt_object_get_min_size_x(const struct NTObject* obj)
{

    return obj->_min_width;
}

ssize_t nt_object_get_min_size_y(const struct NTObject* obj)
{

    return obj->_min_height;
}

ssize_t nt_object_get_max_size_x(const struct NTObject* obj)
{

    return obj->_max_width;
}

ssize_t nt_object_get_max_size_y(const struct NTObject* obj)
{

    return obj->_max_height;
}

void nt_object_set_start_x(struct NTObject* obj, size_t new_start_x)
{

    obj->_rel_start_x = new_start_x;
}

void nt_object_set_start_y(struct NTObject* obj, size_t new_start_y)
{

    obj->_rel_start_y = new_start_y;
}

void nt_object_set_end_x(struct NTObject* obj, size_t new_end_x)
{

    obj->_rel_end_x = new_end_x;
}

void nt_object_set_end_y(struct NTObject* obj, size_t new_end_y)
{
    obj->_rel_end_y = new_end_y;
}

void nt_object_set_pref_size_x(struct NTObject* obj, ssize_t new_pref_size_x)
{

    new_pref_size_x = nt_misc_max(NT_OBJECT_PREF_SIZE_UNSPECIFIED, new_pref_size_x);
    obj->_pref_width = new_pref_size_x;
}

void nt_object_set_pref_size_y(struct NTObject* obj, ssize_t new_pref_size_y)
{

    new_pref_size_y = nt_misc_max(NT_OBJECT_PREF_SIZE_UNSPECIFIED, new_pref_size_y);
    obj->_pref_height = new_pref_size_y;
}

void nt_object_set_min_size_x(struct NTObject* obj, ssize_t new_min_size_x)
{

    obj->_min_width = new_min_size_x;
}

void nt_object_set_min_size_y(struct NTObject* obj, ssize_t new_min_size_y)
{

    obj->_min_height = new_min_size_y;
}

void nt_object_set_max_size_x(struct NTObject* obj, ssize_t new_max_size_x)
{

    obj->_max_width = new_max_size_x;
}

void nt_object_set_max_height(struct NTObject* obj, ssize_t new_max_size_y)
{

    obj->_max_height = new_max_size_y;
}

struct NTContainer* nt_object_get_parent(const struct NTObject* obj)
{

    return obj->_parent;
}

// ------------------------------------------------------------------------------------------------------------------------------------

void nt_object_set_object_position_based_on_dimensions(struct NTObject* obj, size_t start_x, size_t start_y, size_t width, size_t height)
{
    
    if((width == 0) || (height == 0))
    {
        obj->_rel_start_x = 0;
        obj->_rel_start_y = 0;
        obj->_rel_end_x = 0;
        obj->_rel_end_y = 0;
    }
    else
    {
        obj->_rel_start_x = start_x;
        obj->_rel_start_y = start_y;
        obj->_rel_end_x = start_x + width;
        obj->_rel_end_y = start_y + height;
    }
}

int _nt_object_is_object_drawn(struct NTObject* obj)
{

    size_t obj_height = nt_object_calculate_height(obj);
    size_t obj_width = nt_object_calculate_width(obj);

    if((obj_width == 0) && (obj_height == 0)) return 0; // not drawn

    return 1;

}
