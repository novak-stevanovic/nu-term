#include "nt_component/base/nt_simple_pane.h"
#include "nt_shared/nt_display_cell.h"

static nt_override void _pane_arrange_buffer_func(NTPane* pane);

/* -------------------------------------------------------------------------- */

void nt_simple_pane_init(NTSimplePane* simple_pane, 

        nt_abstract void (*simple_pane_get_cell_at_func)(
            struct NTSimplePane* simple_pane, size_t x, size_t y,
            NTDisplayCell* out_display_cell),

        nt_override void (*object_calculate_content_req_size_func)(
            const NTObject* pane, size_t* out_width, size_t* out_height))
{
    nt_pane_init((NTPane*)simple_pane,
            _pane_arrange_buffer_func,
            object_calculate_content_req_size_func);

}

/* -------------------------------------------------------------------------- */

static nt_override void _pane_arrange_buffer_func(NTPane* pane)
{
    NTObject* pane_obj = (NTObject*)pane;
    NTSimplePane* spane = (NTSimplePane*)pane;

    const NTBounds* content_bounds = nt_object_get_content_bounds(pane_obj);

    size_t width, height;

    nt_bounds_calculate_size(content_bounds, &width, &height);

    NTDrawBuffer* draw_buffer = &pane->_draw_buffer;
    size_t i, j;
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            spane->_simple_pane_get_cell_at_func(spane, j, i, 
                    &draw_buffer->_buffer[i][j]);
        }
    }

}
