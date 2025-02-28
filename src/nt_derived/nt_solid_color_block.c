#include "nt_derived/nt_solid_color_block.h"
#include "nt_shared/nt_display_cell.h"

static void _object_arrange_func(NTObject* solid_color_block);

static void _object_get_req_size_func(const NTObject* solid_color_block,
        size_t* out_width, size_t* out_height);

static NTDisplayCell _window_get_content_at_func(const NTWindow* solid_color_block,
        size_t x, size_t y);



void nt_solid_color_block_init(NTSolidColorBlock* solid_color_block, nt_color color)
{
    nt_window_init((NTWindow*)solid_color_block, _object_get_req_size_func, _object_arrange_func, _window_get_content_at_func);

    solid_color_block->_color = color;
}

nt_color nt_solid_color_block_get_color(const NTSolidColorBlock* solid_color_block)
{
    return solid_color_block->_color;
}

void nt_solid_color_block_set_color(NTSolidColorBlock* solid_color_block, nt_color color_code)
{
    solid_color_block->_color = color_code;
    // TODO - redraw
}

static void _object_arrange_func(NTObject* solid_color_block) {}

static void _object_get_req_size_func(const NTObject* solid_color_block,
        size_t* out_width, size_t* out_height)
{
    *out_width = 0;
    *out_height = 0;
}

static NTDisplayCell _window_get_content_at_func(const NTWindow* solid_color_block,
        size_t x, size_t y)
{
    NTSolidColorBlock* _solid_color_block = (NTSolidColorBlock*)solid_color_block;

    NTDisplayCell display_cell;
    nt_display_cell_init_empty(&display_cell, _solid_color_block->_color);

    return display_cell;
}
