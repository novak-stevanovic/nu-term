#ifndef _NT_DRAW_CELL_H_
#define _NT_DRAW_CELL_H_

#include "nt_env/nt_gfx.h"

typedef enum NTDrawCellType { NT_DRAW_CELL_TYPE_REGULAR,
    NT_DRAW_CELL_TYPE_OVERLAY,
    NT_DRAW_CELL_TYPE_TRANSPARENT } NTDrawCellType;

/* This struct acts as a cell inside an NTDrawGrid. The draw grid is used
 * by the NTPane to store its content(content for displaying).
 * These cells may be:
 * 1. 'Regular' cells have both background and foreground. Example would be
 * a bold letter 'A' on top of a green background.
 * 2. 'Overlay' cells with no background and with foreground. Example would be
 * a bold letter 'A' on top of a 'transparent' background.
 * 3. 'Transparent' cells with no background and no foreground.
 * The latter 2 types are useful in objects that are supposed to be written
 * on top of other objects, while utilizing their background color. */
typedef struct NTDrawCell
{
    NTDrawCellType _type;
    char _content;
    NTColor _fg_color, _bg_color;
    NTStyle _style;
} NTDrawCell;

/* This is used by, for example, solid color blocks to print empty(but still
 * colored) cells */
#define NT_DRAW_CELL_NO_CONTENT ' '

void nt_draw_cell_init_regular(NTDrawCell* draw_cell, char content,
        NTColor fg_color, NTColor bg_color, NTStyle style);

void nt_draw_cell_init_overlay(NTDrawCell* draw_cell, char content,
        NTColor fg_color, NTStyle style);

void nt_draw_cell_init_solid_color(NTDrawCell* draw_cell,
        NTColor bg_color);

bool nt_draw_cell_is_full_transparent(const NTDrawCell* draw_cell);
bool nt_draw_cell_is_overlay(const NTDrawCell* draw_cell);
bool nt_draw_cell_is_regular(const NTDrawCell* draw_cell);

#endif // _NT_DRAW_CELL_H_
