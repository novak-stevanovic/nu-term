#ifndef NT_CURSOR_PRIMS_H
#define NT_CURSOR_PRIMS_H

#include <stddef.h>

#define NT_CPRIM_MOVE_CURSOR_HOME_CODE "\e[H"
#define NT_CPRIM_MOVE_CURSOR_LINE_COL_CODE "\e[%ld;%ldH"
#define NT_CPRIM_MOVE_CURSOR_UP_CODE "\e[%dA"
#define NT_CPRIM_MOVE_CURSOR_DOWN_CODE "\e[%dB"
#define NT_CPRIM_MOVE_CURSOR_RIGHT_CODE "\e[%dC"
#define NT_CPRIM_MOVE_CURSOR_LEFT_CODE "\e[%dD"
#define NT_CPRIM_MOVE_CURSOR_TO_COLUMN_CODE "\e[%dG"

void nt_cprim_move_cursor_home();
void nt_cprim_move_cursor_to_line_col(size_t line, size_t col);
void nt_cprim_move_cursor_up(size_t row_diff);
void nt_cprim_move_cursor_down(size_t row_diff);
void nt_cprim_move_cursor_right(size_t col_diff);
void nt_cprim_move_cursor_left(size_t col_diff);
void nt_cprim_move_cursor_to_col(size_t col);

#endif
