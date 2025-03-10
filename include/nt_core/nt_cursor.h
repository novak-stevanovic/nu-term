#ifndef NT_CURSOR_H
#define NT_CURSOR_H

#include <stddef.h>

void nt_cursor_init();

void nt_cursor_rel_move_x(int col_diff);
void nt_cursor_rel_move_y(int row_diff);
void nt_cursor_rel_move_xy(int col_diff, int row_diff);

void nt_cursor_abs_move_to_x(size_t col);
void nt_cursor_abs_move_to_y(size_t row);
void nt_cursor_abs_move_to_xy(size_t col, size_t row);

size_t nt_cursor_get_abs_x();
size_t nt_cursor_get_abs_y();

void nt_cursor_conform_pos_to_display();

void nt_cursor_hide();
void nt_cursor_show();

void nt_cursor_destruct();

#endif
