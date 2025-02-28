#ifndef NT_DISPLAY_CELL_H
#define NT_DISPLAY_CELL_H

#include "nt_shared/nt_shared.h"
#include <stdbool.h>
#include <sys/types.h>

typedef struct NTDisplayCell
{
    nt_color fg_color_code, bg_color_code;
    char content;
} NTDisplayCell;

void nt_display_cell_init(NTDisplayCell* display_cell, nt_color fg_color_code, nt_color bg_color_code, char content);
void nt_display_cell_init_default(NTDisplayCell* display_cell);
void nt_display_cell_init_empty(NTDisplayCell* display_cell, nt_color color);

void nt_display_cell_assign(NTDisplayCell* dest, NTDisplayCell* src);

bool nt_display_cell_are_equal(NTDisplayCell* display_cell1, NTDisplayCell* display_cell2);
bool nt_display_cell_is_empty(NTDisplayCell* display_cell);
 
#endif // NT_DISPLAY_CELL
