#include "nt_component/base/nt_simple_pane.h"
#include "nt_shared/nt_draw_cell.h"

static nt_override void _pane_arrange_buffer_func(NTPane* pane);

/* -------------------------------------------------------------------------- */

void nt_simple_pane_init(NTSimplePane* simple_pane, 

        nt_abstract void (*simple_pane_get_cell_at_func)(
            struct NTSimplePane* simple_pane, size_t x, size_t y,
            NTDrawCell* out_display_cell),

        nt_override void (*object_calculate_content_req_size_func)(
            const NTObject* pane, size_t* out_width, size_t* out_height))
{
    nt_pane_init((NTPane*)simple_pane,
            _pane_arrange_buffer_func,
            object_calculate_content_req_size_func);

    simple_pane->_simple_pane_get_cell_at_func = simple_pane_get_cell_at_func;
}

/* -------------------------------------------------------------------------- */

static nt_override void _pane_arrange_buffer_func(NTPane* pane)
{
    NTSimplePane* spane = (NTSimplePane*)pane;

    size_t width, height;

    NTDrawBuffer* draw_buffer = &(pane->_draw_buffer);
    nt_draw_buffer_get_size(draw_buffer, &width, &height);

    size_t i, j;
    NTDrawCell* curr_cell;
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            curr_cell = NT_DRAW_BUFFER_GET_CELL_AT(draw_buffer, j, i);

            spane->_simple_pane_get_cell_at_func(spane, j, i, curr_cell);
        }
    }

}
