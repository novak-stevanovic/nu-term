#ifndef _NT_DISPLAY_CELL_H_
#define _NT_DISPLAY_CELL_H_

#include "nt_env/base/nt_gfx.h"

typedef struct NTDisplayCell
{
    bool _transparent;
    NTColor _fg_color, _bg_color;
    NTStyle _style;
    char _content;
} NTDisplayCell;

void nt_display_cell_init(NTDisplayCell* display_cell,
        NTColor bg_color, NTColor fg_color, NTStyle style, char content);

void nt_display_cell_init_solid_color(NTDisplayCell* display_cell, NTColor color);

void nt_display_cell_init_default(NTDisplayCell* display_cell);

void nt_display_cell_init_transparent(NTDisplayCell* display_cell);

#endif // _NT_DISPLAY_CELL_H_
