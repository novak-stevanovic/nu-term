#include <assert.h>

#include "nt_base/nt_object.h"
#include "nt_base/nt_constraints.h"
#include "nt_log.h"
#include "nt_misc.h"

void nt_object_init(struct NTObject* obj,
        void (*draw_content_func)(struct NTObject*, struct NTConstraints*),
        void (*get_children_func)(const struct NTObject*, struct Vector*))
{
    assert(obj != NULL);
    assert(draw_content_func != NULL);

    obj->_pref_size_x = NT_OBJECT_SIZE_UNSPECIFIED;
    obj->_pref_size_y = NT_OBJECT_SIZE_UNSPECIFIED;
    obj->_min_size_x = NT_OBJECT_MIN_SIZE_UNSPECIFIED;
    obj->_min_size_y = NT_OBJECT_MIN_SIZE_UNSPECIFIED;
    obj->_max_size_x = NT_OBJECT_MAX_SIZE_UNSPECIFIED;
    obj->_max_size_y = NT_OBJECT_MAX_SIZE_UNSPECIFIED;
    obj->_rel_start_x = 0;
    obj->_rel_start_y = 0;
    obj->_rel_end_x = 0;
    obj->_rel_end_y = 0;

    obj->_draw_content_func = draw_content_func;
    obj->_get_children_func = get_children_func;

    obj->_parent = NULL;
}

void nt_object_draw(struct NTObject* obj, struct NTConstraints* constraints)
{
    assert(obj != NULL);
    assert(obj->_draw_content_func != NULL);

    // printf("Drawing obj: %p with constraints: %ld %ld %ld %ld\n", obj,
    //         constraints->_min_width,
    //         constraints->_min_height,
    //         constraints->_max_width,
    //         constraints->_max_height);

    if(obj->_draw_content_func) obj->_draw_content_func(obj, constraints);
}

// TODO
void nt_object_draw_self_bounded(struct NTObject* obj)
{
    assert(obj != NULL);
    assert(obj->_draw_content_func != NULL);

    struct NTConstraints constraints;
    // nt_object_bounds_init(&constraints, obj->_min_size_x, obj->_min_size_y, obj->_max_size_x, obj->_max_size_y);
    nt_constraints_init(&constraints, 0, 0, 0, 0);

    nt_object_draw(obj, &constraints);
}

size_t nt_object_calculate_abs_start_x(const struct NTObject* obj)
{
    assert(obj != NULL);

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
    assert(obj != NULL);

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
    assert(obj != NULL);

    return nt_object_calculate_abs_start_x(obj) + nt_object_get_end_x(obj) - nt_object_get_start_x(obj);
}

size_t nt_object_calculate_abs_end_y(const struct NTObject* obj)
{
    assert(obj != NULL);

    return nt_object_calculate_abs_start_y(obj) + nt_object_get_end_y(obj) - nt_object_get_start_y(obj);
}

size_t nt_object_calculate_height(const struct NTObject* obj)
{
    assert(obj != NULL);

    return obj->_rel_end_y - obj->_rel_start_y;
}

size_t nt_object_calculate_width(const struct NTObject* obj)
{
    assert(obj != NULL);

    return obj->_rel_end_x - obj->_rel_start_x;
}

size_t nt_object_get_start_x(const struct NTObject* obj)
{
    assert(obj != NULL);

    return obj->_rel_start_x;
}

size_t nt_object_get_start_y(const struct NTObject* obj)
{
    assert(obj != NULL);

    return obj->_rel_start_y;
}

size_t nt_object_get_end_x(const struct NTObject* obj)
{
    assert(obj != NULL);

    return obj->_rel_end_x;
}

size_t nt_object_get_end_y(const struct NTObject* obj)
{
    assert(obj != NULL);

    return obj->_rel_end_y;
}

ssize_t nt_object_get_pref_size_x(const struct NTObject* obj)
{
    assert(obj != NULL);

    return obj->_pref_size_x;
}

ssize_t nt_object_get_pref_size_y(const struct NTObject* obj)
{
    assert(obj != NULL);

    return obj->_pref_size_y;
}

ssize_t nt_object_get_min_size_x(const struct NTObject* obj)
{
    assert(obj != NULL);

    return obj->_min_size_x;
}

ssize_t nt_object_get_min_size_y(const struct NTObject* obj)
{
    assert(obj != NULL);

    return obj->_min_size_y;
}

ssize_t nt_object_get_max_size_x(const struct NTObject* obj)
{
    assert(obj != NULL);

    return obj->_max_size_x;
}

ssize_t nt_object_get_max_size_y(const struct NTObject* obj)
{
    assert(obj != NULL);

    return obj->_max_size_y;
}

void nt_object_set_start_x(struct NTObject* obj, size_t new_start_x)
{
    assert(obj != NULL);

    obj->_rel_start_x = new_start_x;
}

void nt_object_set_start_y(struct NTObject* obj, size_t new_start_y)
{
    assert(obj != NULL);

    obj->_rel_start_y = new_start_y;
}

void nt_object_set_end_x(struct NTObject* obj, size_t new_end_x)
{
    assert(obj != NULL);

    obj->_rel_end_x = new_end_x;
}

void nt_object_set_end_y(struct NTObject* obj, size_t new_end_y)
{
    assert(obj != NULL);

    obj->_rel_end_y = new_end_y;
}

void nt_object_set_pref_size_x(struct NTObject* obj, ssize_t new_pref_size_x)
{
    assert(obj != NULL);

    // new_pref_size_x = nt_misc_max(NT_OBJECT_SIZE_UNSPECIFIED, new_pref_size_x);
    nt_log_log("old px: %d new px: %d\n", obj->_pref_size_x, new_pref_size_x);
    obj->_pref_size_x = new_pref_size_x;
}

void nt_object_set_pref_size_y(struct NTObject* obj, ssize_t new_pref_size_y)
{
    assert(obj != NULL);

    // nt_log_log("old py: %d new py: %d\n", obj->_pref_size_y, new_pref_size_y);
    new_pref_size_y = nt_misc_max(NT_OBJECT_SIZE_UNSPECIFIED, new_pref_size_y);
    obj->_pref_size_y = new_pref_size_y;
}

void nt_object_set_min_size_x(struct NTObject* obj, ssize_t new_min_size_x)
{
    assert(obj != NULL);

    obj->_min_size_x = new_min_size_x;
}

void nt_object_set_min_size_y(struct NTObject* obj, ssize_t new_min_size_y)
{
    assert(obj != NULL);

    obj->_min_size_y = new_min_size_y;
}

void nt_object_set_max_size_x(struct NTObject* obj, ssize_t new_max_size_x)
{
    assert(obj != NULL);

    obj->_max_size_x = new_max_size_x;
}

void nt_object_set_max_size_y(struct NTObject* obj, ssize_t new_max_size_y)
{
    assert(obj != NULL);

    obj->_max_size_y = new_max_size_y;
}

struct NTContainer* nt_object_get_parent(const struct NTObject* obj)
{
    assert(obj != NULL);

    return obj->_parent;
}

void nt_object_get_children(const struct NTObject* obj, struct Vector* vec_buff)
{
    assert(obj != NULL);
    assert(vec_buff != NULL);
    assert(obj->_get_children_func != NULL);

    obj->_get_children_func(obj, vec_buff);
}

// ------------------------------------------------------------------------------------------------------------------------------------

void _nt_object_set_object_position_based_on_dimensions(struct NTObject* obj, size_t start_x, size_t start_y, size_t width, size_t height)
{
    assert(obj != NULL);
    
    if(((width != 0) && (height == 0)) || ((width == 0) && (height != 0))) assert(1 != 1); // impossible state

    if((width == 0) && (height == 0))
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
        obj->_rel_end_x = width;
        obj->_rel_end_y = height;
    }
}
//
// int _nt_object_is_object_drawn(struct NTObject* obj)
// {
//     assert(obj != NULL);
//
//     size_t obj_height = nt_object_calculate_height(obj);
//     size_t obj_width = nt_object_calculate_width(obj);
//     size_t start_x = obj->_rel_start_x;
//     size_t start_y = obj->_rel_start_y;
//
//     if((obj_width == 0) && (obj_height == 0)) return 0; // not drawn
//     if(((obj_width == 0) && (obj_height != 0)) || ((obj_height == 0) && (obj_width != 0))) assert(1 != 1); // impossible state
//
//     if((start_x != 0) && (obj_width == 0)) assert(1 != 1); // impossible state
//     if((start_y != 0) && (obj_height == 0)) assert(1 != 1); // impossible state
//
//     return 1;
//
// }
