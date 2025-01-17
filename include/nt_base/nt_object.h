#ifndef NT_OBJECT_H
#define NT_OBJECT_H

#include <stddef.h>

struct NTContainer;
struct Vector;

struct NTObject
{
    size_t _rel_start_x, _rel_start_y, _rel_end_x, _rel_end_y;
    size_t _pref_size_x, _pref_size_y;

    struct NTContainer* _parent;

    void (*_draw_func)(struct NTObject*, void*);
    struct Vector* (*_get_children_func)(struct NTObject*);
};

void nt_object_init(struct NTObject* obj,
        struct NTContainer* parent,
        void (*draw_func)(struct NTObject*, void*),
        struct Vector* (*get_children_func)(struct NTObject*));

void nt_object_draw(struct NTObject* obj);

size_t nt_object_get_start_x(const struct NTObject* obj);
size_t nt_object_get_start_y(const struct NTObject* obj);
size_t nt_object_get_end_x(const struct NTObject* obj);
size_t nt_object_get_end_y(const struct NTObject* obj);
size_t nt_object_get_pref_size_x(const struct NTObject* obj);
size_t nt_object_get_pref_size_y(const struct NTObject* obj);

struct NTContainer* nt_object_get_parent(const struct NTObject* obj);

struct Vector* nt_object_get_children(struct NTObject* obj);

void nt_object_set_start_x(struct NTObject* obj, size_t new_start_x);
void nt_object_set_start_y(struct NTObject* obj, size_t new_start_y);
void nt_object_set_end_x(struct NTObject* obj, size_t new_end_x);
void nt_object_set_end_y(struct NTObject* obj, size_t new_end_y);
void nt_object_set_pref_size_x(struct NTObject* obj, size_t new_pref_size_x);
void nt_object_set_pref_size_y(struct NTObject* obj, size_t new_pref_size_y);

#endif
