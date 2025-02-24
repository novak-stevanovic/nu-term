#ifndef NT_DISPLAY_CELL_H
#define NT_DISPLAY_CELL_H

#include <stdbool.h>
#include <sys/types.h>

struct NTDisplayCell
{
    ssize_t fg_color_code, bg_color_code;
    char content;
};

void nt_display_cell_init(struct NTDisplayCell* display_cell, ssize_t fg_color_code, ssize_t bg_color_code, char content);

void nt_display_cell_init_default(struct NTDisplayCell* display_cell);

void nt_display_cell_assign(struct NTDisplayCell* dest, struct NTDisplayCell* src);

bool nt_display_cell_are_equal(struct NTDisplayCell* display_cell1, struct NTDisplayCell* display_cell2);

#endif
