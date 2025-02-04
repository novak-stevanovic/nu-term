#include <assert.h>

#include "nt_derived/nt_solid_color_block.h"
#include "nt_core/nt_color.h"
#include "nt_shared/nt_display_cell.h"

void nt_solid_color_block_init(struct NTSolidColorBlock* solid_color_block, size_t color_code)
{
    assert(solid_color_block != NULL);

    nt_window_init((struct NTWindow*)solid_color_block,
            _nt_solid_color_block_calculate_required_size_func,
            _nt_solid_color_block_draw_window_func,
            _nt_solid_color_block_get_content_at_func, NT_DRAW_ENGINE_LOW_DRAW_PRIORITY);

    solid_color_block->_color_code = color_code;
}

size_t nt_solid_color_block_get_color(struct NTSolidColorBlock* solid_color_block)
{
    assert(solid_color_block != NULL);

    return solid_color_block->_color_code;
}

void nt_solid_color_block_set_color(struct NTSolidColorBlock* solid_color_block, size_t color_code)
{
    assert(solid_color_block != NULL);

    // TODO DRAW AGAIN?
    solid_color_block->_color_code = color_code;
}

void _nt_solid_color_block_get_content_at_func(struct NTWindow* solid_color_block, size_t x, size_t y, struct NTDisplayCell* display_cell_buff)
{
    assert(solid_color_block != NULL);
    assert(display_cell_buff != NULL);

    struct NTSolidColorBlock* _solid_color_block = (struct NTSolidColorBlock*)solid_color_block;
    display_cell_buff->bg_color_code = _solid_color_block->_color_code;
    display_cell_buff->fg_color_code = NT_COLOR_DEFAULT;
    display_cell_buff->content = ' '; // TODO
}

void _nt_solid_color_block_draw_window_func(struct NTWindow* solid_color_block, size_t size_x, size_t size_y)
{
    assert(solid_color_block != NULL);
}

void _nt_solid_color_block_calculate_required_size_func(struct NTWindow* solid_color_block, size_t* required_x, size_t* required_y)
{
    assert(solid_color_block != NULL);
    assert(required_x != NULL);
    assert(required_y != NULL);

    *required_x = 0;
    *required_y = 0;
}
