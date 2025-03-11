#include "nt_shared/nt_display_cell.h"

#define NO_CONTENT ' '

void nt_display_cell_init(NTDisplayCell* display_cell,
        NTColor bg_color, NTColor fg_color, NTStyle style, char content)
{
    if(display_cell == NULL) return;

    display_cell->_bg_color = bg_color;
    display_cell->_fg_color = fg_color;
    display_cell->_style = style;
    display_cell->_content = content;
    display_cell->_transparent = false;
}

void nt_display_cell_init_solid_color(NTDisplayCell* display_cell, NTColor color)
{
    nt_display_cell_init(display_cell, color, NT_COLOR_DEFAULT,
            NT_STYLE_DEFAULT, NO_CONTENT);
}

void nt_display_cell_init_default(NTDisplayCell* display_cell)
{
    nt_display_cell_init(display_cell, NT_COLOR_DEFAULT, NT_COLOR_DEFAULT,
            NT_STYLE_DEFAULT, NO_CONTENT);
}

void nt_display_cell_init_transparent(NTDisplayCell* display_cell)
{
    nt_display_cell_init_default(display_cell);
    display_cell->_transparent = true;
}
