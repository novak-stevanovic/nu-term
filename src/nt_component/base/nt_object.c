#include "nt_component/base/nt_object.h"
#include "nt_core/nt_platform.h"
#include "nt_env/nt_draw_engine.h"
#include "nt_shared/nt_shared.h"
#include "nt_util/nt_log.h"

#include <assert.h>

/* -------------------------------------------------------------------------- */

// NTPlatform


/* -------------------------------------------------------------------------- */

void nt_object_init(NTObject* object,

        nt_override void (*object_arrange_content_func)(NTObject* object),

        nt_override void (*object_display_content_func)(NTObject* object),

        nt_override void (*object_calculate_content_req_size_func)(
            const NTObject* object,
            size_t* out_width, size_t* out_height))

{
    object->_object_calculate_content_req_size_func =
        object_calculate_content_req_size_func;
    object->_object_display_content_func = object_display_content_func;
    object->_object_arrange_content_func = object_arrange_content_func;

    object->_pref_height = NT_PREF_SIZE_UNSPECIFIED;
    object->_pref_width = NT_PREF_SIZE_UNSPECIFIED;

    object->_parent = NULL;

    object->_anchor = NULL;
    object->_anchored_count = 0;
    object->_z_index = NT_OBJECT_DEFAULT_Z_INDEX;

    nt_bounds_init_def(&object->_bounds, NULL);

    nt_bounds_init_def(&object->_content_offset_bounds, &object->_bounds);

    // nt_ext_style_init();

    nt_object_update_required_size(object);
}

// TODO - update for padding, border
// TODO - propagate
void nt_object_update_required_size(NTObject* object)
{
    size_t width, height;

    object->_object_calculate_content_req_size_func(object, &width, &height);
}

// ---------------------------------------------------------

/* NTDrawEngine interface */

void _nt_object_arrange(NTObject* object, bool arrange_anchored)
{
    if(arrange_anchored)
    {
        size_t i;
        for(i = 0; i < object->_anchored_count; i++)
            _nt_object_arrange(object->_anchored_objects[i], true);
    }

    if(object->_object_arrange_content_func)
        object->_object_arrange_content_func(object);
}

void _nt_object_display(NTObject* object)
{
    size_t i;
    for(i = 0; i < object->_anchored_count; i++) // display lower-level objects
    {
        if(object->_anchored_objects[i]->_z_index > NT_OBJECT_DEFAULT_Z_INDEX)
            break;

        _nt_object_display(object->_anchored_objects[i]);
    }

    if(object->_object_display_content_func)
        object->_object_display_content_func(object);

    for(; i < object->_anchored_count; i++) // display higher-level objects
        _nt_object_display(object->_anchored_objects[i]);
}

// ---------------------------------------------------------

// Pref size
void nt_object_set_pref_size(NTObject* object,
        ssize_t new_pref_width, ssize_t new_pref_height)
{
    object->_pref_width = new_pref_width;
    object->_pref_height = new_pref_height;
    
    // TODO - update, propagate
}
void nt_object_set_pref_width(NTObject* object, ssize_t new_pref_width)
{
    object->_pref_width = new_pref_width;
    // TODO - update, propagate
}
void nt_object_set_pref_height(NTObject* object, ssize_t new_pref_height)
{
    object->_pref_height = new_pref_height;
    // TODO - update, propagate
}

void nt_object_get_pref_size(const NTObject* object,
        ssize_t* out_pref_width, ssize_t* out_pref_height)
{
    if(out_pref_width != NULL) *out_pref_width = object->_pref_width;
    if(out_pref_height != NULL) *out_pref_height = object->_pref_height;
}

ssize_t nt_object_get_pref_width(const NTObject* object)
{
    return object->_pref_width;
}

ssize_t nt_object_get_pref_height(const NTObject* object)
{
    return object->_pref_height;
}

// ---------------------------------------------------------

// Required size
void nt_object_get_req_size(const NTObject* object,
        ssize_t* out_req_width, ssize_t* out_req_height)
{
    if(out_req_width != NULL) *out_req_width = object->_cached_req_width;
    if(out_req_height != NULL) *out_req_height = object->_cached_req_height;
}

size_t nt_object_get_req_width(const NTObject* object)
{
    return object->_cached_req_width;
}

size_t nt_object_get_req_height(const NTObject* object)
{
    return object->_cached_req_height;
}

// ---------------------------------------------------------

// Bounds
static void _update_content_bounds(NTObject* object);

void _nt_object_set_bounds(NTObject* object, const NTBounds* new_bounds)
{
    object->_bounds = *new_bounds;

    _update_content_bounds(object);
}

const NTBounds* nt_object_get_bounds(const NTObject* object)
{
    return &object->_bounds;
}

const NTBounds* nt_object_get_content_bounds(const NTObject* object)
{
    return &object->_content_offset_bounds;
}

/* -------------------------------------------------------------------------- */

static void _update_content_bounds(NTObject* object)
{
    size_t object_width, object_height;

    nt_bounds_calculate_size(&object->_bounds, &object_width, &object_height);

    nt_bounds_set_values(&object->_content_offset_bounds,
            0, 0, object_width, object_height);

}
