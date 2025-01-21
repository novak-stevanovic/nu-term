#ifndef NT_OBJECT_H
#define NT_OBJECT_H

#include <stddef.h>
#include <stdio.h>

struct NTContainer;
struct Vector;

/* This structure is primarily used by the functions nt_object_draw_inside_bounds() and the internal function _draw_content_func()  
 * within the NTObject structure. A pointer to this structure is passed as a parameter in the following contexts:  
 * 1. When the function nt_object_draw_inside_bounds(struct NTObject* child, struct NTObjectBounds* bounds) is called,  
 *    it is invoked by the parent container for its child. The child (and, by extension, its own children)  
 *    must not exceed the defined minimum and maximum sizes when setting its dimensions.  
 * 2. When the function nt_object_draw_content(struct NTObject* obj, struct NTObjectBounds* bounds) is called,  
 *    the object's content must adhere to the provided size constraints.  
 *    - If the object is a window, its content should be positioned within the specified bounds.  
 *    - If the object is a container, its children should be arranged so that they collectively respect these size limits.  
 * Fields used_x and used_y act as return values. When the function returns, these fields should be set so that they
 * reflect dimensions occupied by the object(and it's children) in question. */
struct NTObjectBounds
{
    ssize_t _min_size_x, _min_size_y; // read-only
    ssize_t _max_size_x, _max_size_y; // read-only

    ssize_t used_x, used_y;
};

/* This structures represents an abstract object inside this GUI framework. 
 * TODO
*   void (*_draw_content_func)(struct NTObject*, struct NTObjectBounds*) - function that will draw content of an object inside
*   the provided bounds. The object itself may be a container or a window, meaning that the content may be other objects as well.
*   This should be done the following way(if the object is a container) - 
*   1. for each child:
*   a) set start coordinates of child
*   b) determine minimum and maximum dimensions for the child
*   c) invoke nt_object_draw(child, bounds)
*   2. calculate used_x and used_y by the children and set the fields in the bounds object argument
*   3. invoke the post_set_size_func(object) if existant
*
*   struct Vector* (*_get_children_func)(const struct NTObject*) - function that returns children of an ntobject. This may be NULL.
*   void (*_post_set_size_func)(struct NTObject*) - function called after setting start and end coordinates of an object. 
*   This function may be used for setting bounds for a container's background(because the bounds align with the
*   container's start and end coordinates) or some other misc work. */
struct NTObject
{
    size_t _rel_start_x, _rel_start_y, _rel_end_x, _rel_end_y;
    size_t _pref_size_x, _pref_size_y;

    struct NTContainer* _parent;

    void (*_draw_content_func)(struct NTObject*, struct NTObjectBounds*);
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

void nt_object_draw_self_bounded(struct NTObject* obj);
void nt_object_draw_inside_bounds(struct NTObject* obj, struct NTObjectBounds* bounds);

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
