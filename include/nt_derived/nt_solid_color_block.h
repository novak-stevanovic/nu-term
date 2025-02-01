#ifndef NT_SOLID_COLOR_BLOCK_H
#define NT_SOLID_COLOR_BLOCK_H

#include "nt_base/nt_window.h"

struct NTContainer;

struct NTSolidColorBlock
{
    struct NTWindow _base;
    size_t _color_code;
};

void nt_solid_color_block_init(struct NTSolidColorBlock* solid_color_block, size_t color_code);
size_t nt_solid_color_block_get_color(struct NTSolidColorBlock* solid_color_block);
void nt_solid_color_block_set_color(struct NTSolidColorBlock* solid_color_block, size_t color_code);

void _nt_solid_color_block_get_content_at_func(struct NTWindow* solid_color_block, size_t x, size_t y, struct NTDisplayCell* display_cell_buff);
void _nt_solid_color_block_draw_window_func(struct NTWindow* solid_color_block, struct NTObjectSizeConstraints* constraints);

#endif
