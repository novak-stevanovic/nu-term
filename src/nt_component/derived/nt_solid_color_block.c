#include "nt_component/derived/nt_solid_color_block.h"
#include "nt_shared/nt_display_cell.h"

static nt_override void _simple_pane_get_cell_at_func(
        NTSimplePane* solid_color_block, size_t x, size_t y,
        NTDisplayCell* out_display_cell);

static nt_override void _object_calculate_content_req_size_func(
        const NTObject* solid_color_block,
        size_t* out_width, size_t* out_height);

/* -------------------------------------------------------------------------- */

void nt_solid_color_block_init(NTSolidColorBlock* solid_color_block,
        NTColor bg_color)
{
    nt_simple_pane_init((NTSimplePane*)solid_color_block,
            _simple_pane_get_cell_at_func,
            _object_calculate_content_req_size_func);

    solid_color_block->_bg_color = bg_color;
}

static nt_override void _simple_pane_get_cell_at_func(
        NTSimplePane* solid_color_block, size_t x, size_t y,
        NTDisplayCell* out_display_cell)
{
    if(out_display_cell != NULL)
    {
        NTSolidColorBlock* _solid_color_block = (NTSolidColorBlock*)solid_color_block;
        nt_display_cell_init_solid_color(out_display_cell,
                _solid_color_block->_bg_color);
    }
}

static nt_override void _object_calculate_content_req_size_func(
        const NTObject* solid_color_block,
        size_t* out_width, size_t* out_height)
{
    if(out_width != NULL) *out_width = 0;
    if(out_height != NULL) *out_height = 0;
}
