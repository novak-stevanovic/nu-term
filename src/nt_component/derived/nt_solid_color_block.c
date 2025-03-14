#include "nt_component/derived/nt_solid_color_block.h"
#include "nt_core/nt_platform.h"
#include "nt_env/nt_draw_engine.h"
#include "nt_shared/nt_draw_cell.h"

static nt_override void _simple_pane_get_cell_at_func(
        NTSimplePane* solid_color_block, size_t x, size_t y,
        NTDrawCell* out_draw_cell);

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

struct __SetColorReq
{
    NTSolidColorBlock* scb;
    NTColor new_bg_color;
};

static void __nt_scb_set_color(void* _set_color_req)
{
    struct __SetColorReq* set_color_req = (struct __SetColorReq*)_set_color_req;

    set_color_req->scb->_bg_color = set_color_req->new_bg_color;
    // nt_draw_engine_draw_object_tree((NTObject*)set_color_req->scb);
}

void nt_solid_color_block_set_color(NTSolidColorBlock* solid_color_block,
        NTColor new_bg_color)
{
    struct __SetColorReq req;
    req.scb = solid_color_block;
    req.new_bg_color = new_bg_color;

    nt_platform_execute(__nt_scb_set_color, &req, sizeof(struct __SetColorReq));
    nt_draw_engine_draw_object_tree((NTObject*)solid_color_block);
}

/* -------------------------------------------------------------------------- */

static nt_override void _simple_pane_get_cell_at_func(
        NTSimplePane* solid_color_block, size_t x, size_t y,
        NTDrawCell* out_draw_cell)
{
    if(out_draw_cell != NULL)
    {
        NTSolidColorBlock* _solid_color_block =
            (NTSolidColorBlock*)solid_color_block;

        nt_draw_cell_init_solid_color(out_draw_cell,
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
