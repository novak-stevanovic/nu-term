#include "nt_derived/nt_solid_color_block.h"
#include "nt_shared/nt_display_cell.h"

static struct NTDisplayCell _nt_solid_color_block_get_content_at_func(struct NTWindow* solid_color_block, size_t x, size_t y);

void nt_solid_color_block_init(struct NTSolidColorBlock* solid_color_block, size_t color_code,
        NTDrawEngineDrawPriority draw_priority)
{
    nt_simple_window_init((struct NTSimpleWindow*)solid_color_block,
            _nt_solid_color_block_get_content_at_func, draw_priority);

    solid_color_block->_color_code = color_code;
}

size_t nt_solid_color_block_get_color(struct NTSolidColorBlock* solid_color_block)
{
    return solid_color_block->_color_code;
}

void nt_solid_color_block_set_color(struct NTSolidColorBlock* solid_color_block, size_t color_code)
{
    solid_color_block->_color_code = color_code;
    // TODO REDRAW
}

static struct NTDisplayCell _nt_solid_color_block_get_content_at_func(struct NTWindow* solid_color_block, size_t x, size_t y)
{
    struct NTSolidColorBlock* _solid_color_block = (struct NTSolidColorBlock*)solid_color_block;

    struct NTDisplayCell display_cell;
    display_cell.fg_color_code = 9;
    display_cell.bg_color_code = _solid_color_block->_color_code;
    display_cell.content = ' ';

    return display_cell;
}
