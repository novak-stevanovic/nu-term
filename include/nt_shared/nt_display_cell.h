#ifndef NT_DISPLAY_CELL_H
#define NT_DISPLAY_CELL_H

#include <sys/types.h>

#define NT_DISPLAY_CELL_COLOR_UNDEFINED -1
#define NT_DISPLAY_CELL_CONTENT_UNDEFINED ' '

struct NTDisplayCell
{
    ssize_t fg_color_code, bg_color_code;
    char content;
};

void nt_display_cell_init(struct NTDisplayCell* display_cell, ssize_t fg_color_code, ssize_t bg_color_code, char content);

void nt_display_cell_assign(struct NTDisplayCell* dest, struct NTDisplayCell* src);

#endif
