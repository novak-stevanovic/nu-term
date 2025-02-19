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

void nt_display_cell_assign(struct NTDisplayCell* dest, struct NTDisplayCell* src)
{

    *dest = *src;
}
