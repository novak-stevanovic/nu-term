#ifndef _NT_OBJECT_H_
#define _NT_OBJECT_H_

#include "nt_shared/nt_bounds.h"
#include "nt_shared/nt_shared.h"
#include <stdlib.h>

#define NT_OBJECT_MAX_ANCHORED 10
#define NT_OBJECT_DEFAULT_Z_INDEX 0

typedef ssize_t nt_z_index;

struct NTContainer;
typedef struct NTContainer NTContainer;

typedef struct NTObject
{
    NTContainer* _parent;

    /* Anchoring information */
    struct NTObject* _anchor;
    struct NTObject* _anchored_objects[NT_OBJECT_MAX_ANCHORED];
    size_t _anchored_count;
    nt_z_index _z_index;

    /* Coordinates in parent's coordinate system. */
    NTBounds _bounds;

    /* Offset from NTObject's start_x and start_y coordinates. */
    NTBounds _content_offset_bounds;

    /* Sizes */
    size_t _cached_req_width, _cached_req_height;
    size_t _pref_width, _pref_height;

    /* TODO: explain */
    nt_abstract void (*_object_arrange_content_func)(struct NTObject* object);
    /* TODO: explain */
    nt_abstract void (*_object_display_content_func)(struct NTObject* object);

    /* TODO: explain */
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

// Main
void nt_object_arrange(NTObject* object);
void nt_object_display(NTObject* object);
void nt_object_update_required_size(NTObject* object);

// Pref size
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

// Anchor stuff - ?

// Bounds
const NTBounds* nt_object_get_bounds(const NTObject* object);
const NTBounds* nt_object_get_content_bounds(const NTObject* object);
void nt_object_set_bounds(NTObject* object, const NTBounds* new_bounds);

NTContainer* nt_object_get_parent(const NTObject* object);

#endif // _NT_OBJECT_H_
