#include "nt_component/derived/nt_solid_color_block.h"

#include "nt_core/platform/nt_platform.h"
#include "nt_core/platform/nt_platform_request.h"
#include "nt_core/engine/nt_draw_engine.h"
#include "nt_shared/nt_draw_cell.h"

/* NT_PLATFORM -------------------------------------------------------------- */

nt_platform struct _SetColorData
{
    NTSolidColorBlock* scb;
    NTColor new_bg_color;
};

nt_platform static void _set_color_func(void* _set_color_req)
{
    struct _SetColorData* set_color_req = (struct _SetColorData*)_set_color_req;

    set_color_req->scb->_bg_color = set_color_req->new_bg_color;
    nt_draw_engine_draw_object_tree((NTObject*)set_color_req->scb);
}

/* -------------------------------------------------------------------------- */

nt_override static void _simple_pane_get_cell_at_func(
        NTSimplePane* solid_color_block, size_t x, size_t y,
        NTDrawCell* out_draw_cell);

nt_override static void _object_calculate_content_req_size_func(
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

void nt_solid_color_block_set_color(NTSolidColorBlock* solid_color_block,
        NTColor new_bg_color)
{
    struct _SetColorData data;
    data.scb = solid_color_block;
    data.new_bg_color = new_bg_color;

    NTPlatformRequest req;
    nt_platform_request_init(&req, _set_color_func,
            &data, sizeof(struct _SetColorData));

    nt_platform_execute(&req);
}

/* -------------------------------------------------------------------------- */

nt_override static void _simple_pane_get_cell_at_func(
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

nt_override static void _object_calculate_content_req_size_func(
        const NTObject* solid_color_block,
        size_t* out_width, size_t* out_height)
{
    if(out_width != NULL) *out_width = 0;
    if(out_height != NULL) *out_height = 0;
}
