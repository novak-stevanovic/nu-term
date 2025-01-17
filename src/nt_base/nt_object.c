#include <assert.h>

#include "nt_base/nt_object.h"

void nt_object_init(struct NTObject* obj,
        struct NTContainer* parent,
        void (*draw_func)(struct NTObject*, void*),
        struct Vector* (*get_children_func)(const struct NTObject*))
{
    assert(obj != NULL);
    assert(draw_func != NULL);

    obj->_pref_size_x = 0;
    obj->_pref_size_y = 0;
    obj->_rel_start_x = 0;
    obj->_rel_start_y = 0;
    obj->_rel_end_x = 0;
    obj->_rel_end_y = 0;

    obj->_parent = parent;

    obj->_draw_func = draw_func;
    obj->_get_children_func = get_children_func;
}

void nt_object_draw(struct NTObject* obj)
{
    assert(obj != NULL);
    assert(obj->_draw_func != NULL);

    obj->_draw_func(obj, NULL);
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

size_t nt_object_get_pref_size_x(const struct NTObject* obj)
{
    assert(obj != NULL);

    return obj->_pref_size_x;
}

size_t nt_object_get_pref_size_y(const struct NTObject* obj)
{
    assert(obj != NULL);

    return obj->_pref_size_y;
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

void nt_object_set_pref_size_x(struct NTObject* obj, size_t new_pref_size_x)
{
    assert(obj != NULL);

    obj->_pref_size_x = new_pref_size_x;
}

void nt_object_set_pref_size_y(struct NTObject* obj, size_t new_pref_size_y)
{
    assert(obj != NULL);

    obj->_pref_size_y = new_pref_size_y;
}

struct NTContainer* nt_object_get_parent(const struct NTObject* obj)
{
    assert(obj != NULL);

    return obj->_parent;
}

struct Vector* nt_object_get_children(const struct NTObject* obj)
{
    assert(obj != NULL);

    return obj->_get_children_func(obj);
}
