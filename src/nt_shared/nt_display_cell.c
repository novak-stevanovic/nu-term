#include <stdlib.h>

#include "nt_shared/nt_display_cell.h"
#include "nt_core/nt_color.h"

void nt_display_cell_init(struct NTDisplayCell* display_cell, ssize_t fg_color_code, ssize_t bg_color_code, char content)
{
    size_t color_count = nt_color_get_color_count();

    display_cell->fg_color_code = fg_color_code;
    display_cell->bg_color_code = bg_color_code;
    display_cell->content = content;
}

void nt_display_cell_init_default(struct NTDisplayCell* display_cell)
{
    nt_display_cell_init(display_cell, 9, 9, ' ');
}

void nt_display_cell_assign(struct NTDisplayCell* dest, struct NTDisplayCell* src)
{
    dest->content = src->content;
    dest->fg_color_code = src->fg_color_code;
    dest->bg_color_code = src->bg_color_code;
}

bool nt_display_cell_are_equal(struct NTDisplayCell* display_cell1, struct NTDisplayCell* display_cell2)
{
    return ((display_cell1->bg_color_code == display_cell2->bg_color_code) &&
            (display_cell1->fg_color_code == display_cell2->fg_color_code) &&
            (display_cell1->content == display_cell2->content));
}
