
#include "nt_derived/nt_solid_color_block.h"
#include "nt_core/nt_color.h"
#include "nt_shared/nt_display_cell.h"

static void _nt_solid_color_block_init(struct NTSolidColorBlock* solid_color_block, size_t color_code,
        NTDrawEngineDrawPriority draw_priority)
{

    nt_window_init((struct NTWindow*)solid_color_block,
            _nt_solid_color_block_calculate_required_size_func,
            _nt_solid_color_block_draw_window_func,
            _nt_solid_color_block_get_content_at_func, draw_priority);

    solid_color_block->_color_code = color_code;
}

void nt_solid_color_block_init_default(struct NTSolidColorBlock* solid_color_block, size_t color_code)
{
    _nt_solid_color_block_init(solid_color_block, color_code, NT_DRAW_ENGINE_HIGH_DRAW_PRIORITY);
}

void nt_solid_color_block_init_background(struct NTSolidColorBlock* solid_color_block, size_t color_code)
{
    _nt_solid_color_block_init(solid_color_block, color_code, NT_DRAW_ENGINE_LOW_DRAW_PRIORITY);
}

size_t nt_solid_color_block_get_color(struct NTSolidColorBlock* solid_color_block)
{

    return solid_color_block->_color_code;
}

void nt_solid_color_block_set_color(struct NTSolidColorBlock* solid_color_block, size_t color_code)
{
    // TODO DRAW AGAIN?
    solid_color_block->_color_code = color_code;
}

void _nt_solid_color_block_get_content_at_func(struct NTWindow* solid_color_block, size_t x, size_t y, struct NTDisplayCell* display_cell_buff)
{

    struct NTSolidColorBlock* _solid_color_block = (struct NTSolidColorBlock*)solid_color_block;
    display_cell_buff->bg_color_code = _solid_color_block->_color_code;
    display_cell_buff->fg_color_code = 0;
    display_cell_buff->content = ' '; // TODO
}

void _nt_solid_color_block_draw_window_func(struct NTWindow* solid_color_block, size_t size_x, size_t size_y)
{
}

void _nt_solid_color_block_calculate_required_size_func(struct NTWindow* solid_color_block, size_t* required_x, size_t* required_y)
{

    *required_x = 0;
    *required_y = 0;
}
