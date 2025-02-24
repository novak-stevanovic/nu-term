#ifndef NT_OBJECT_H
#define NT_OBJECT_H

#include <stddef.h>
#include <stdio.h>

struct NTContainer;
struct NTConstraints;

/* This structures represents an abstract object inside this GUI framework. 
 * TODO 
 * _draw_content_func is the function responsible for drawing an object's content on the screen. More specifically, the 'drawing', has
 * different meanings based on the type of the NTObject. If the NTObject is:
 * 1) a window(has actual content) - then it may perform some internal logic that will position letters and colors
 * depending on the object's position/size. The window will be added to NTDrawEngine's draw queue and will be displayed on the screen
 * when the NTDrawEngine's draw function is invoked. More information in nt_window.h file.
 *
 * 2) a container(has other objects inside) - then it may perform some internal logic to position its children, determine the sizes, and
 * draw the objects the container contains. More information in nt_container.h file.
 * This function has 2 parameters: pointer to an object that is to be drawn and a pointer to an object that holds information about where
 * and how much drawing is to be done - this is usually determined by the parent. More specifically, here are the following rules: 
 * 1. When _draw_content_func is invoked, the passed NTConstraints object's constraints must be respected. 
 * 2. _draw_content_func must define used_x and used_y fields in the NTConstraints object. The caller will determine the NTObject's
 * position based on these values. This means that, when an object is deciding its size(used_x and used_y), it may decide
 * not to appear on the screen - by setting used_x and used_y to 0. This will tell the parent container to mark the child as 'undrawn'. 
 * The object may decide this for any reason - it doesn't like the provided size constraints, for example. This is however, only possible if the given constraints allow
 * for height and width to be equal to 0. */
#define NT_OBJECT_PREF_SIZE_UNSPECIFIED -1
#define NT_OBJECT_MIN_SIZE_UNSPECIFIED 0
#define NT_OBJECT_MAX_SIZE_UNSPECIFIED 100000

struct NTBaseDrawDataObject
{
    size_t used_x, used_y;
};

enum NTDrawMode { NT_DRAW_MODE_DRAW, NT_DRAW_MODE_PSEUDO };

struct NTObject
{
    size_t _rel_start_x, _rel_start_y, _rel_end_x, _rel_end_y;
    size_t _min_width, _min_height;
    ssize_t _pref_width, _pref_height;
    size_t _max_width, _max_height;

    struct NTContainer* _parent;

    // NT_OBJECT_DRAW() ------------------------------------------------------------------

    struct NTBaseDrawDataObject* (*_object_draw_init_func)(struct NTObject* object,
            struct NTConstraints* constraints);
    // ^ initializes NTBaseDrawDataObject by dynamically allocating the object.

    void (*_object_draw_arrange_func)(struct NTObject* object, 
            struct NTBaseDrawDataObject* data_object,
            struct NTConstraints* constraints, enum NTDrawMode draw_mode);
    // ^ pretends to arrange content of the object by placing the required data inside
    // the data_object. Must update used_x and used_y fields in NTBaseDrawDataObject
    // to fit the given constraints.
    // NON-NULL
    
    void (*_object_draw_full_draw_func)(struct NTObject* object,
            struct NTBaseDrawDataObject* data_object);
    // ^ perform full draw - this means, for a window, to update its content buffer(if existent)
    // for a container, position its children via nt_object_set_position.
    // NON-NULL

    void (*_object_draw_conclude_func)(struct NTObject* object,
            struct NTBaseDrawDataObject* data_object);
    // ^ concludes the draw - use this to clean up dynamically allocated memory,
    // etc(do not use this to free data_object(it will be freed automatically)

    // -----------------------------------------------------------------------------------
};

void nt_object_init(struct NTObject* object,

    struct NTBaseDrawDataObject* (*object_draw_init_func)(struct NTObject* object, struct NTConstraints* constraints),

    void (*object_draw_arrange_func)(struct NTObject* object,
            struct NTBaseDrawDataObject* data_object, struct NTConstraints* constraints, enum NTDrawMode draw_mode),
    
    void (*object_draw_full_draw_func)(struct NTObject* object,
            struct NTBaseDrawDataObject* data_object),

    void (*object_draw_conclude_func)(struct NTObject* object,
            struct NTBaseDrawDataObject* data_object));

// Useful only for very simple objects
struct NTBaseDrawDataObject* nt_object_base_draw_data_object_create();

void nt_object_base_draw_data_object_init(struct NTBaseDrawDataObject* data_object);

void nt_object_draw(struct NTObject* obj,
        struct NTConstraints* constraints,
        enum NTDrawMode draw_mode,
        size_t* out_width, size_t* out_height);

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
ssize_t nt_object_get_pref_width(const struct NTObject* obj);
ssize_t nt_object_get_pref_height(const struct NTObject* obj);
ssize_t nt_object_get_min_width(const struct NTObject* obj);
ssize_t nt_object_get_min_height(const struct NTObject* obj);
ssize_t nt_object_get_max_width(const struct NTObject* obj);
ssize_t nt_object_get_max_height(const struct NTObject* obj);

struct NTContainer* nt_object_get_parent(const struct NTObject* obj);

void nt_object_set_start_x(struct NTObject* obj, size_t new_start_x);
void nt_object_set_start_y(struct NTObject* obj, size_t new_start_y);
void nt_object_set_end_x(struct NTObject* obj, size_t new_end_x);
void nt_object_set_end_y(struct NTObject* obj, size_t new_end_y);
void nt_object_set_pref_width(struct NTObject* obj, ssize_t new_pref_width);
void nt_object_set_pref_height(struct NTObject* obj, ssize_t new_pref_height);
void nt_object_set_min_width(struct NTObject* obj, ssize_t new_min_width);
void nt_object_set_min_height(struct NTObject* obj, ssize_t new_min_height);
void nt_object_set_max_width(struct NTObject* obj, ssize_t new_max_width);
void nt_object_set_max_height(struct NTObject* obj, ssize_t new_max_height);

// -----------------------------------------------------------------------------------------------------------------------

void nt_object_set_object_position_based_on_dimensions(struct NTObject* obj, size_t start_x, size_t start_y, size_t width, size_t height);
// int _nt_object_is_object_drawn(struct NTObject* obj);

#endif
