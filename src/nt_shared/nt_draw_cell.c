#include "nt_shared/nt_draw_cell.h"

void nt_draw_cell_init_regular(NTDrawCell* draw_cell, char content,
        NTColor fg_color, NTColor bg_color, NTStyle style)
{
    draw_cell->_type = NT_DRAW_CELL_TYPE_REGULAR;

    draw_cell->_fg_color = fg_color;
    draw_cell->_bg_color = bg_color;
    draw_cell->_style = style;
    draw_cell->_content = content;
}

void nt_draw_cell_init_overlay(NTDrawCell* draw_cell, char content,
        NTColor fg_color, NTStyle style)
{
    draw_cell->_type = NT_DRAW_CELL_TYPE_OVERLAY;

    draw_cell->_content = content;
    draw_cell->_fg_color = fg_color;
    draw_cell->_style = style;

    draw_cell->_bg_color = NT_COLOR_DEFAULT;
}

void nt_draw_cell_init_solid_color(NTDrawCell* draw_cell,
        NTColor bg_color)
{
    draw_cell->_type = NT_DRAW_CELL_TYPE_REGULAR;

    draw_cell->_bg_color = bg_color;

    draw_cell->_style = NT_STYLE_DEFAULT;
    draw_cell->_fg_color = NT_COLOR_DEFAULT;
    draw_cell->_content = NT_DRAW_CELL_NO_CONTENT;
}

bool nt_draw_cell_is_full_transparent(const NTDrawCell* draw_cell)
{
    return (draw_cell->_type == NT_DRAW_CELL_TYPE_TRANSPARENT);
}

bool nt_draw_cell_is_overlay(const NTDrawCell* draw_cell)
{
    return (draw_cell->_type == NT_DRAW_CELL_TYPE_OVERLAY);
}

bool nt_draw_cell_is_regular(const NTDrawCell* draw_cell)
{
    return (draw_cell->_type == NT_DRAW_CELL_TYPE_REGULAR);
}
