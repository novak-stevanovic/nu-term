#include "nt_component/base/nt_pane.h"
#include "nt_shared/nt_shared.h"

static nt_override void _object_display_content_func(NTObject* object);
static nt_override void _object_arrange_content_func(NTObject* object);

/* -------------------------------------------------------------------------- */

void nt_pane_init(NTPane* pane, 

        nt_override void (*pane_arrange_buffer_func)(NTPane* pane),

        nt_override void (*object_calculate_content_req_size_func)(
            const NTObject* pane, size_t* out_width, size_t* out_height))
{

    nt_object_init((NTObject*)pane,
            _object_arrange_content_func,
            _object_display_content_func,
            object_calculate_content_req_size_func);

    nt_draw_buffer_init(&pane->_draw_buffer);
}

const NTDrawBuffer* nt_pane_get_draw_buffer(const NTPane* pane)
{
    return &pane->_draw_buffer;
}

/* -------------------------------------------------------------------------- */

static nt_override void _object_display_content_func(NTObject* object)
{
    // TODO
}

static nt_override void _object_arrange_content_func(NTObject* object)
{
    NTPane* pane = (NTPane*)object;

    const NTBounds* bounds = nt_object_get_bounds(object);
    size_t width = nt_bounds_calculate_width(bounds);
    size_t height = nt_bounds_calculate_height(bounds);

    nt_draw_buffer_set_size(&pane->_draw_buffer, width, height);

    if(pane->_pane_arrange_buffer_func != NULL)
        pane->_pane_arrange_buffer_func(pane);
}
