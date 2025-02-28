#include <stdlib.h>

#include "nt_shared/nt_display_cell.h"
#include "nt_core/nt_color.h"

void nt_display_cell_init(struct NTDisplayCell* display_cell, nt_color fg_color_code, nt_color bg_color_code, char content)
{
    size_t color_count = nt_color_get_color_count();

    display_cell->fg_color_code = fg_color_code;
    display_cell->bg_color_code = bg_color_code;
    display_cell->content = content;
}

void nt_display_cell_init_default(NTDisplayCell* display_cell)
{
    nt_display_cell_init(display_cell, NT_COLOR_DEFAULT, NT_COLOR_DEFAULT, 0);
}

void nt_display_cell_init_empty(struct NTDisplayCell* display_cell, nt_color cell_color)
{
    nt_display_cell_init(display_cell, NT_COLOR_DEFAULT, cell_color, ' ');
}

void nt_display_cell_assign(struct NTDisplayCell* dest, struct NTDisplayCell* src)
{
    (*dest) = (*src);
}

bool nt_display_cell_are_equal(struct NTDisplayCell* display_cell1, struct NTDisplayCell* display_cell2)
{
    return ((display_cell1->bg_color_code == display_cell2->bg_color_code) &&
            (display_cell1->fg_color_code == display_cell2->fg_color_code) &&
            (display_cell1->content == display_cell2->content));
}

bool nt_display_cell_is_empty(NTDisplayCell* display_cell)
{
    return (display_cell->content != ' ');
}
