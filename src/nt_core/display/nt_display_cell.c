#include "nt_core/display/nt_display_cell.h"

void nt_display_cell_init(NTDisplayCell* display_cell)
{
    display_cell->_content = NT_DRAW_CELL_NO_CONTENT;
    display_cell->_bg_color = NT_COLOR_DEFAULT;
    display_cell->_fg_color = NT_COLOR_DEFAULT;
    display_cell->_style = NT_STYLE_DEFAULT;

    display_cell->_fg_pane = NULL;
    display_cell->_bg_pane = NULL;
}

void nt_display_cell_update(NTDisplayCell* display_cell,
        NTDrawCell draw_cell, NTPane* pane)
{
    if(nt_draw_cell_is_overlay(&draw_cell))
    {
        display_cell->_content = draw_cell._content;
        display_cell->_style = draw_cell._style;
        display_cell->_fg_color = draw_cell._fg_color;

        display_cell->_fg_pane = pane;
    }
    else if(nt_draw_cell_is_full_transparent(&draw_cell)) {}
    else // regular cell
    {
        display_cell->_content = draw_cell._content;
        display_cell->_style = draw_cell._style;
        display_cell->_fg_color = draw_cell._fg_color;
        display_cell->_fg_pane = pane;

        display_cell->_bg_color = draw_cell._bg_color;
        display_cell->_bg_pane = pane;
    }
}
