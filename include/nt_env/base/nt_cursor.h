#ifndef _NT_CURSOR_H_
#define _NT_CURSOR_H_

#include <stdbool.h>
#include <stdlib.h>

void _nt_cursor_init();
void _nt_cursor_destruct();

void nt_cursor_move_home();

void nt_cursor_rel_move_x(ssize_t col_diff);
void nt_cursor_rel_move_y(ssize_t row_diff);
void nt_cursor_rel_move_xy(ssize_t col_diff, ssize_t row_diff);

void nt_cursor_abs_move_to_x(size_t col);
void nt_cursor_abs_move_to_y(size_t row);
void nt_cursor_abs_move_to_xy(size_t col, size_t row);

// size_t nt_cursor_get_x();
// size_t nt_cursor_get_y();
// bool nt_cursor_is_visible();

void nt_cursor_conform_pos_to_display();

void nt_cursor_hide();
void nt_cursor_show();

#endif // _NT_CURSOR_H_
