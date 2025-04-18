#include "nt_component/base/nt_pane.h"
#include "nt_core/display/nt_display.h"
#include "nt_shared/nt_shared.h"

nt_override static void _object_display_content_func(NTObject* object);
nt_override static void _object_arrange_content_func(NTObject* object);

/* -------------------------------------------------------------------------- */

void nt_pane_init(NTPane* pane, 

        nt_abstract void (*pane_arrange_buffer_func)(struct NTPane* pane,
            size_t width, size_t height),

        nt_override void (*object_calculate_content_req_size_func)(
            const NTObject* pane, size_t* out_width, size_t* out_height))
{

    nt_object_init((NTObject*)pane,
            _object_arrange_content_func,
            _object_display_content_func,
            object_calculate_content_req_size_func);

    pane->_pane_arrange_buffer_func = pane_arrange_buffer_func;

    nt_draw_buffer_init(&pane->_draw_buffer);
}

NTDrawBuffer* nt_pane_get_draw_buffer(NTPane* pane)
{
    return &pane->_draw_buffer;
}

/* -------------------------------------------------------------------------- */

nt_override static void _object_display_content_func(NTObject* object)
{
    _nt_display_draw_pane_to_buffer((NTPane*)object);
}

nt_override static void _object_arrange_content_func(NTObject* object)
{
    NTPane* pane = (NTPane*)object;

    const NTBounds* bounds = nt_object_get_content_bounds(object);
    size_t width = nt_bounds_calculate_width(bounds);
    size_t height = nt_bounds_calculate_height(bounds);

    _nt_draw_buffer_set_size(&pane->_draw_buffer, width, height);

    if(pane->_pane_arrange_buffer_func != NULL)
        pane->_pane_arrange_buffer_func(pane, width, height);
}
