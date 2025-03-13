#ifndef _NT_DISPLAY_CELL_H_
#define _NT_DISPLAY_CELL_H_

#include "nt_shared/nt_draw_cell.h"

typedef struct NTPane NTPane;

/* NTDisplayCell is a cell inside the display buffer. It is useful in the
 * cases where a pane is layered on top of another pane and overwriting
 * needs to happen. There are multiple scenarios:
 * 1. The overwriting cell is a 'regular cell' - all content of the internal
 * draw cell is overwritten.
 * 2. The overwriting cell is a 'transparent cell' - no overwriting happens.
 * 3. The overwriting cell is an 'overlay cell' - the foreground of the
 * internal draw cell is overwritten. 
 * This is done through calling nt_display_cell_update().
 * On top of that, these display cells also track the 'owner' pane of both
 * background and foreground content. '*/
typedef struct NTDisplayCell
{
    // Foreground
    char _content;
    NTStyle _style;
    NTColor _fg_color;
    NTPane* _fg_pane;

    // Background
    NTColor _bg_color;
    NTPane* _bg_pane;
} NTDisplayCell;

void nt_display_cell_init(NTDisplayCell* display_cell);

/* Determines which part of display_cell's draw_cell to update based on
 * 'draw_cell' type, as explained above.
 * Updates _fg_pane and _bg_pane if needed. */
void nt_display_cell_update(NTDisplayCell* display_cell, NTDrawCell draw_cell,
        NTPane* pane);

#endif // _NT_DISPLAY_CELL_H_
