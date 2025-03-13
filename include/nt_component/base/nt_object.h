#ifndef _NT_OBJECT_H_
#define _NT_OBJECT_H_

#include <stdlib.h>

#include "nt_shared/nt_bounds.h"
#include "nt_shared/nt_shared.h"

#define NT_OBJECT_MAX_ANCHORED 10
#define NT_OBJECT_DEFAULT_Z_INDEX 0

typedef ssize_t nt_z_index;

struct NTContainer;
typedef struct NTContainer NTContainer;

/* NTObject is the core UI element in the NT framework. It stores layout data 
 * (bounds and offsets), manages parent/anchored relationships,
 * and supports layering via z-index. It uses polymorphic functions for 
 * arranging, displaying, and sizing content, forming the foundation this
 * library. */
typedef struct NTObject
{
    NTContainer* _parent;

    /* Other objects may be anchored to another object. They must not in any way
     * depend upon the anchor's internal state(content, content bounds). Objects
     * with a higher z-index will be written later, allowing them to overwrite
     * anything that is in a layer below. Whenever an object changes size and is
     * arranged, anchored objects are arranged too. Whenever an object is display,
     * anchored objects are displayed too. */
    struct NTObject* _anchor;
    struct NTObject* _anchored_objects[NT_OBJECT_MAX_ANCHORED];
    size_t _anchored_count;
    nt_z_index _z_index;

    /* Coordinates in parent's coordinate system.
     * Object's size can be inferred from these bounds.
     * The parent is responsible for calculating their values and
     * setting them. */
    NTBounds _bounds;

    /* Offset from NTObject's start_x and start_y coordinates.
     * Object's content size can be inferred from these bounds. 
     * This is useful for applying 'external style' to an object
     * (padding, border). The object's content will take up all
     * the remaining space. 
     * The values are calculated internally, based on 'external
     * style'. They are updated automatically, every time the
     * _bounds of an object change. */
    NTBounds _content_offset_bounds;

    /* Sizes */
    size_t _cached_req_width, _cached_req_height;
    ssize_t _pref_width, _pref_height;

    /* INTERNAL FUNCTION
     * This function should arrange the content inside an object based on its
     * current state. If the object's content is consisted of:
     *
     * 1) Concrete content(text, colors... etc), such as a NTDrawCell grid,
     * this function must rearrange these cells(or their values) inside the
     * grid so that the new arrangement reflects how the object wants
     * to be displayed on the screen.
     *
     * 2) Other objects - this object represents a container of these objects.
     * In this case, the object must set the bounds of its children(through
     * _nt_object_set_bounds) and call _nt_object_arrange() for any children
     * that change its size.
     *
     * When the function is called, it is assumed that the object's _bounds
     * and _content_offset_bounds are up to date. This means that the
     * available space for this function to work with can be calculated
     * based on _content_offset_bounds.
     *
     * This function is not meant to be called directly but 
     * through _nt_object_arrange(). */
    nt_abstract void (*_object_arrange_content_func)(struct NTObject* object);

    /* INTERNAL FUNCTION
     * This function should, display the object's internal content by writing
     * the content onto the display buffer inside nt_display.h. 
     * If the object is a container, it must propagate this call throughout the
     * object tree - to its children. */
    nt_abstract void (*_object_display_content_func)(struct NTObject* object);

    /* This function should calculate the width and height an object's content 
     * needs to properly show up on the screen. If the object's content is 
     * consisted of:
     * 1) Concrete content - this function must calculate how much space
     * the object's content requires(both width and height).
     *
     * 2) Other objects - this function must calculate how much space
     * is required so that all content(children) is displayed properly
     * (this means that this function must take into account children'
     * s preferred size and only after its required size) 
     * 
     * This function should not take into account 'external style' options
     * (padding, border).
     * This function must not base its calculations on the state of other
     * objects(excluding the pref and req sizes of its children)
     * Values are returned through 'out' parameters. The function should assume
     * that one of the pointers could be NULL. */
    nt_abstract void (*_object_calculate_content_req_size_func)(
            const struct NTObject* object,
            size_t* out_width, size_t* out_height);

} NTObject;

void nt_object_init(NTObject* object,

    nt_override void (*object_arrange_content_func)(NTObject* object),

    nt_override void (*object_display_content_func)(NTObject* object),

    nt_override void (*object_calculate_content_req_size_func)(
            const NTObject* object,
            size_t* out_width, size_t* out_height));

// Pref size -- TODO - propagate to parent
void nt_object_set_pref_size(NTObject* object,
        ssize_t new_pref_width, ssize_t new_pref_height);
void nt_object_set_pref_width(NTObject* object, ssize_t new_pref_width);
void nt_object_set_pref_height(NTObject* object, ssize_t new_pref_height);

void nt_object_get_pref_size(const NTObject* object,
        ssize_t* out_pref_width, ssize_t* out_pref_height);
ssize_t nt_object_get_pref_width(const NTObject* object);
ssize_t nt_object_get_pref_height(const NTObject* object);

// Required size
void nt_object_get_req_size(const NTObject* object,
        ssize_t* out_req_width, ssize_t* out_req_height);
size_t nt_object_get_req_width(const NTObject* object);
size_t nt_object_get_req_height(const NTObject* object);

/* Recalculates required size based on the object's 
 * _object_calculate_req_size_func, takes into account 'external style' options
 * (padding, border) and updates the object's _cached_req_width, _cached_req_height
 * fields. This function must be invoked after any internal change that
 * occurs in an object. */
void nt_object_update_required_size(NTObject* object);

NTContainer* nt_object_get_parent(const NTObject* object);

// Anchor stuff - ?
//

const NTBounds* nt_object_get_bounds(const NTObject* object);
const NTBounds* nt_object_get_content_bounds(const NTObject* object);

/* This function sets an object's _bounds to 'new_bounds'. Afterwards,
 * it recalculates its _content_offset_bounds and updates them. This function
 * does not call _nt_object_arrange() afterwards for the sake of control,
 * but if the previous size of _bounds does not match the size
 * of 'new_bounds', a call to _nt_object_arrange() is mandatory.
 * This function is an internal function used by containers. */
void _nt_object_set_bounds(NTObject* object, const NTBounds* new_bounds);

/* This function performs a call to _object_arrange_content_func. 
 * This function should be called in 2 cases:
 * 1. If the internal state of an object has changed(for example, if a text
 * inside a text label has changed). This means that the object
 * must reposition its content. In this case, parameter 'arrange_anchored'
 * should be 0.
 * 2. If the bounds of an object change. This means that the object
 * must reposition its content but so do the anchored objects(their size
 * might have changed). In this case, parameter 'arrange_anchored'
 * should be 1. 
 * This function is an internal function used by containers. */
void _nt_object_arrange(NTObject* object, bool arrange_anchored);

/* This function performs a call to _object_display_content_func.
 * Anchored objects must be re-displayed to respect the layering(so that
 * objects on top, if existent, will overwrite objects on bottom).
 * This function is an internal function used by NTContainer and NTDrawEngine. */
void _nt_object_display(NTObject* object);

#endif // _NT_OBJECT_H_
