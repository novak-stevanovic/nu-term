#include <assert.h>

#include "nt_base/nt_object.h"

void nt_object_init(struct NTObject* obj,
        struct NTContainer* parent,
        void (*draw_content_func)(struct NTObject*, struct NTObjectSizeConstraints*),
        void (*get_children_func)(const struct NTObject*, struct Vector*))
{
    assert(obj != NULL);
    assert(draw_content_func != NULL);

    obj->_pref_size_x = 0;
    obj->_pref_size_y = 0;
    obj->_rel_start_x = 0;
    obj->_rel_start_y = 0;
    obj->_rel_end_x = 0;
    obj->_rel_end_y = 0;

    obj->_parent = parent;

    obj->_draw_content_func = draw_content_func;
    obj->_get_children_func = get_children_func;
}

void nt_object_size_constraints_init(struct NTObjectSizeConstraints* constraints,
        ssize_t min_size_x, ssize_t min_size_y,
        ssize_t max_size_x, ssize_t max_size_y)
{
    assert(constraints != NULL);

    constraints->_max_size_x = max_size_x;
    constraints->_max_size_y = max_size_y;
    constraints->_min_size_x = min_size_x;
    constraints->_min_size_y = min_size_y;

    constraints->used_x = -1;
    constraints->used_y = -1;
}

void nt_object_draw(struct NTObject* obj, struct NTObjectSizeConstraints* constraints)
{
    assert(obj != NULL);
    assert(obj->_draw_content_func != NULL);

    if(obj->_draw_content_func) obj->_draw_content_func(obj, constraints);
}

void nt_object_draw_self_bounded(struct NTObject* obj)
{
    assert(obj != NULL);
    assert(obj->_draw_content_func != NULL);

    struct NTObjectSizeConstraints constraints;
    // nt_object_bounds_init(&constraints, obj->_min_size_x, obj->_min_size_y, obj->_max_size_x, obj->_max_size_y);
    nt_object_size_constraints_init(&constraints, 0, 0, 0, 0);

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
        curr_obj = (struct NTObject*)curr_parent;
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

    return nt_object_calculate_abs_start_x(obj) + nt_object_get_end_x(obj) - nt_object_get_start_x(obj) - 1;
}

size_t nt_object_calculate_abs_end_y(const struct NTObject* obj)
{
    assert(obj != NULL);

    return nt_object_calculate_abs_start_y(obj) + nt_object_get_end_y(obj) - nt_object_get_start_y(obj) - 1;
}

size_t nt_object_calculate_height(const struct NTObject* obj)
{
    assert(obj != NULL);

    return obj->_rel_end_y - obj->_rel_start_y + 1;
}

size_t nt_object_calculate_width(const struct NTObject* obj)
{
    assert(obj != NULL);

    return obj->_rel_end_x - obj->_rel_start_x + 1;
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

    obj->_pref_size_x = new_pref_size_x;
}

void nt_object_set_pref_size_y(struct NTObject* obj, ssize_t new_pref_size_y)
{
    assert(obj != NULL);

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
