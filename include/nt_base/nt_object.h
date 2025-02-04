#ifndef NT_OBJECT_H
#define NT_OBJECT_H

#include <stddef.h>
#include <stdio.h>

struct NTContainer;
struct NTConstraints;
struct Vector;

/* This structures represents an abstract object inside this GUI framework. 
 * TODO 
 * _draw_content_func is the function responsible for drawing an object's content on the screen. More specifically, the 'drawing', has
 * different meanings based on the type of the NTObject. If the NTObject is:
 * 1) a window(has actual content) - then it may perform some internal logic that will position letters and colors
 * depending on the object's position/size. The window will be added to NTDrawEngine's draw queue and will be displayed on the screen
 * when the NTDrawEngine's draw function is invoked.
 *
 * 2) a container(has other objects inside) - then it may perform some internal logic to positio it's children, determine the sizes, and
 * draw the objects the container contains. More information in nt_container.h file.
 * This function has 2 parameters: pointer to an object that is to be drawn and a pointer to an object that holds information about where
 * and how much drawing is to be done - this is usually determined by the parent. More specifically, here are the following rules: 
 * 1. When _draw_content_func is invoked for an NTObject, the NTObject will have it's _rel_start_x and _rel_start_y set.
 * 2. When _draw_content_func is invoked, the passed NTObjectSizeConstraints object's constraints must be respected. 
 * 3. _draw_content_func must define used_x and used_y fields in the NTObjectSizeConstraints object. The caller will determine the NTObject's
 * end positions based on these values. */
#define NT_OBJECT_SIZE_UNSPECIFIED -1
#define NT_OBJECT_MIN_SIZE_UNSPECIFIED 0
#define NT_OBJECT_MAX_SIZE_UNSPECIFIED 100000
struct NTObject
{
    size_t _rel_start_x, _rel_start_y, _rel_end_x, _rel_end_y;
    size_t _min_size_x, _min_size_y;
    ssize_t _pref_size_x, _pref_size_y;
    size_t _max_size_x, _max_size_y;

    struct NTContainer* _parent;

    void (*_draw_content_func)(struct NTObject*, struct NTConstraints*);
    void (*_get_children_func)(const struct NTObject*, struct Vector*);
};

void nt_object_init(struct NTObject* obj,
        void (*draw_content_func)(struct NTObject*, struct NTConstraints*),
        void (*get_children_func)(const struct NTObject*, struct Vector*));

void nt_object_draw_self_bounded(struct NTObject* obj);
void nt_object_draw(struct NTObject* obj, struct NTConstraints* constraints);

size_t nt_object_calculate_abs_start_x(const struct NTObject* obj);
size_t nt_object_calculate_abs_start_y(const struct NTObject* obj);
size_t nt_object_calculate_abs_end_x(const struct NTObject* obj);
size_t nt_object_calculate_abs_end_y(const struct NTObject* obj);
size_t nt_object_calculate_height(const struct NTObject* obj);
size_t nt_object_calculate_width(const struct NTObject* obj);

size_t nt_object_get_start_x(const struct NTObject* obj);
size_t nt_object_get_start_y(const struct NTObject* obj);
size_t nt_object_get_end_x(const struct NTObject* obj);
size_t nt_object_get_end_y(const struct NTObject* obj);
ssize_t nt_object_get_pref_size_x(const struct NTObject* obj);
ssize_t nt_object_get_pref_size_y(const struct NTObject* obj);
ssize_t nt_object_get_min_size_x(const struct NTObject* obj);
ssize_t nt_object_get_min_size_y(const struct NTObject* obj);
ssize_t nt_object_get_max_size_x(const struct NTObject* obj);
ssize_t nt_object_get_max_size_y(const struct NTObject* obj);

struct NTContainer* nt_object_get_parent(const struct NTObject* obj);

void nt_object_get_children(const struct NTObject* obj, struct Vector* vec_buff);

void nt_object_set_start_x(struct NTObject* obj, size_t new_start_x);
void nt_object_set_start_y(struct NTObject* obj, size_t new_start_y);
void nt_object_set_end_x(struct NTObject* obj, size_t new_end_x);
void nt_object_set_end_y(struct NTObject* obj, size_t new_end_y);
void nt_object_set_pref_size_x(struct NTObject* obj, ssize_t new_pref_size_x);
void nt_object_set_pref_size_y(struct NTObject* obj, ssize_t new_pref_size_y);
void nt_object_set_min_size_x(struct NTObject* obj, ssize_t new_min_size_x);
void nt_object_set_min_size_y(struct NTObject* obj, ssize_t new_min_size_y);
void nt_object_set_max_size_x(struct NTObject* obj, ssize_t new_max_size_x);
void nt_object_set_max_size_y(struct NTObject* obj, ssize_t new_max_size_y);

#endif
