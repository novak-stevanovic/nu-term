#include "nt_base/nt_object.h"

void nt_object_init(NTObject* object, 

    void (*object_calculate_req_size_func)(const NTObject* object,
            size_t* out_width, size_t* out_height),

    void (*object_arrange_func)(NTObject* object),

    void (*object_display_func)(NTObject* object))
{
    object->_object_calculate_req_size_func = object_calculate_req_size_func;
    object->_object_arrange_func = object_arrange_func;
    object->_object_display_func = object_display_func;

    object->_min_width = NT_OBJECT_DEFAULT_MIN_SIZE;
    object->_min_height = NT_OBJECT_DEFAULT_MIN_SIZE;

    object->_max_width = NT_OBJECT_DEFAULT_MAX_SIZE;
    object->_max_height = NT_OBJECT_DEFAULT_MAX_SIZE;

    object->_pref_width = NT_OBJECT_PREF_SIZE_UNSPECIFIED;
    object->_pref_height = NT_OBJECT_PREF_SIZE_UNSPECIFIED;

    object->_parent = NULL;

    object->_tainted = false;

    nt_object_update_required_size(object);
    nt_bounds_init_default(&object->_bounds);
}

void nt_object_arrange(NTObject* object)
{
    if(object->_object_arrange_func) object->_object_arrange_func(object);
}

void nt_object_display(NTObject* object)
{
    if(object->_object_display_func) 
        object->_object_display_func(object);

    object->_tainted = false;
}

NTBounds nt_object_calculate_abs_bounds(const NTObject* object)
{
    ssize_t coordinate_sum_x = 0;
    ssize_t coordinate_sum_y = 0;

    const NTObject* curr_object = object;
    const NTContainer* curr_parent;
    while(curr_object != NULL)
    {
        curr_parent = curr_object->_parent;
        coordinate_sum_x += curr_object->_bounds._start_x;
        coordinate_sum_y += curr_object->_bounds._start_y;
        curr_object = (NTObject*)curr_parent;
    }

    NTBounds bounds;
    nt_bounds_init(&bounds,
            coordinate_sum_x,
            coordinate_sum_y,
            coordinate_sum_x + nt_bounds_calculate_width(&object->_bounds),
            coordinate_sum_y + nt_bounds_calculate_height(&object->_bounds));

    return bounds;
}

size_t nt_object_calculate_abs_start_x(const NTObject* object)
{
    return nt_object_calculate_abs_bounds(object)._start_x;
}

size_t nt_object_calculate_abs_start_y(const NTObject* object)
{
    return nt_object_calculate_abs_bounds(object)._start_y;
}

size_t nt_object_calculate_abs_end_x(const NTObject* object)
{
    return nt_object_calculate_abs_bounds(object)._end_x;
}

size_t nt_object_calculate_abs_end_y(const NTObject* object)
{
    return nt_object_calculate_abs_bounds(object)._end_y;
}

void nt_object_update_required_size(NTObject* object)
{
    size_t width, height;

    object->_object_calculate_req_size_func(object, &width, &height);
    
    object->_required_width = width;
    object->_required_height = height;
}


size_t nt_object_get_min_width(const NTObject* object)
{
    return object->_min_width;
}

size_t nt_object_get_min_height(const NTObject* object)
{
    return object->_min_height;
}

size_t nt_object_get_max_width(const NTObject* object)
{
    return object->_max_width;
}

size_t nt_object_get_max_height(const NTObject* object)
{
    return object->_max_height;
}

const NTBounds* nt_object_get_bounds(const NTObject* object)
{
    return &object->_bounds;
}

void nt_object_set_position(NTObject* object, const NTBounds* new_bounds)
{
    NTBounds old_absolute_bounds = nt_object_calculate_abs_bounds(object);

    object->_bounds = *new_bounds;

    NTBounds new_absolute_bounds = nt_object_calculate_abs_bounds(object);

    if(!nt_bounds_are_equal(&old_absolute_bounds, &new_absolute_bounds))
        object->_tainted = true;

}
