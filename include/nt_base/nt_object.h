#ifndef NT_OBJECT_H
#define NT_OBJECT_H

#include <stddef.h>
#include <stdio.h>

struct NTContainer;
struct Vector;

struct NTObjectSizeConstraints
{
    ssize_t _min_size_x, _min_size_y; // read-only
    ssize_t _max_size_x, _max_size_y; // read-only

    ssize_t used_x, used_y;
};

/* This structures represents an abstract object inside this GUI framework. 
 * TODO 
 * _draw_content_func is the function responsible for displaying an object's content on the screen. If the object is:
 * 1. a window(has actual content) - then it may perform some internal logic that will position letters and colors
 * depending on the object's position/size.
 * 2. a container(has other objects inside) - then it must perform some internal logic that will position its children, determine their sizes...
 * etc.
 * This function has 2 parameters: pointer to an object that is to be drawn and a pointer to an object that holds information about where
 * and how much drawing is to be done - this is determined by the parent. 
 * 1. More specifically - the caller(usually the parent), will set the start_x and start_y coordinates of an object. 
 * 2. Then, based on its limits, and the start coordinates of the child, it will
 * determine how big the child must be(min size and max size fields in struct NTObjectSizeConstraints). 
 * 3. It will create an object and pass its reference: nt_object_draw(child, childs_constraints).
 * The child will determine how much space it's going to use so that:
 * min_size_x <= used_x <= max_used_x. Same for y. The child may also perform the same logic for its children if it's a container - but
 * let's keep it simple. After using up the space, it will update the obj pointed to by child_constraints argument so that it reflects
 * how much of the space allocated to the child it used. The child will peform a return.
 * 4. The parent will set the end coordinates of the child according to used_x and used_y "returned" inside the child_constraints. Then, the 
 * parent will determine the next position and possible size for the next child and the process will repeat. */
struct NTObject
{
    size_t _rel_start_x, _rel_start_y, _rel_end_x, _rel_end_y;
    size_t _pref_size_x, _pref_size_y;

    struct NTContainer* _parent;

    void (*_draw_content_func)(struct NTObject*, struct NTObjectSizeConstraints*);
    struct Vector* (*_get_children_func)(const struct NTObject*);
};

void nt_object_constraints_init(struct NTObjectSizeConstraints* nt_obj_bounds,
        ssize_t min_size_x, ssize_t min_size_y,
        ssize_t max_size_x, ssize_t max_size_y);

void nt_object_init(struct NTObject* obj,
        struct NTContainer* parent,
        void (*draw_content_func)(struct NTObject*, struct NTObjectSizeConstraints*),
        struct Vector* (*get_children_func)(const struct NTObject*));

void nt_object_draw_self_bounded(struct NTObject* obj);
void nt_object_draw(struct NTObject* obj, struct NTObjectSizeConstraints* bounds);

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
