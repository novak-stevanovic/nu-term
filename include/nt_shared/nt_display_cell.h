#ifndef NT_DISPLAY_CELL_H
#define NT_DISPLAY_CELL_H

#include <stddef.h>

struct NTDisplayCell
{
    size_t fg_color_code, bg_color_code;
    char content;
};

void nt_display_cell_assign(struct NTDisplayCell* dest, struct NTDisplayCell* src);

#endif
