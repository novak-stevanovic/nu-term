#ifndef NT_OBJECT_H
#define NT_OBJECT_H

#include <stddef.h>
#include <stdio.h>

struct NTContainer;
struct Vector;

struct NTObjectBounds
{
    ssize_t _min_size_x, _min_size_y; // read-only
    ssize_t _max_size_x, _max_size_y; // read-only

    ssize_t used_x, used_y;
};

struct NTObject
{
    size_t _rel_start_x, _rel_start_y, _rel_end_x, _rel_end_y;
    size_t _pref_size_x, _pref_size_y;

    struct NTContainer* _parent;

    void (*_arrange_content_func)(struct NTObject*, struct NTObjectBounds*);
    struct Vector* (*_get_children_func)(const struct NTObject*);
    void (*_post_set_size_func)(struct NTObject*);
};

void nt_object_bounds_init(struct NTObjectBounds* nt_obj_bounds,
        ssize_t min_size_x, ssize_t min_size_y,
        ssize_t max_size_x, ssize_t max_size_y);

void nt_object_init(struct NTObject* obj,
        struct NTContainer* parent,
        void (*arrange_content_func)(struct NTObject*, struct NTObjectBounds*),
        struct Vector* (*get_children_func)(const struct NTObject*),
        void (*post_set_size_func)(struct NTObject*));

void nt_object_draw_tree(struct NTObject* obj);

size_t nt_object_get_start_x(const struct NTObject* obj);
size_t nt_object_get_start_y(const struct NTObject* obj);
size_t nt_object_get_end_x(const struct NTObject* obj);
size_t nt_object_get_end_y(const struct NTObject* obj);
size_t nt_object_get_pref_size_x(const struct NTObject* obj);
size_t nt_object_get_pref_size_y(const struct NTObject* obj);

struct NTContainer* nt_object_get_parent(const struct NTObject* obj);

struct Vector* nt_object_get_children(const struct NTObject* obj);

void nt_object_set_start_x(struct NTObject* obj, size_t new_start_x);
void nt_object_set_start_y(struct NTObject* obj, size_t new_start_y);
void nt_object_set_end_x(struct NTObject* obj, size_t new_end_x);
void nt_object_set_end_y(struct NTObject* obj, size_t new_end_y);
void nt_object_set_pref_size_x(struct NTObject* obj, size_t new_pref_size_x);
void nt_object_set_pref_size_y(struct NTObject* obj, size_t new_pref_size_y);

#endif
