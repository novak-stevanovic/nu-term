#include <stdlib.h>

#include "nt_core/nt_cursor.h"
#include "nt_core/nt_display.h"
#include "nt_misc.h"
#include "nt_primitives/nt_cursor_prims.h"

ssize_t cursor_x, cursor_y;

// ------------------------------------------------------------------------------------------------------------

void nt_cursor_init()
{
    nt_cprim_move_cursor_home();
}

int nt_cursor_rel_move_x(int col_diff)
{
    if(col_diff == 0) return 0;

    if(col_diff > 0)
        nt_cprim_move_cursor_right(col_diff);
    else
        nt_cprim_move_cursor_left(-col_diff);

    cursor_x += col_diff;
    int status = nt_cursor_conform_pos_to_display();
    return status;
}

int nt_cursor_rel_move_y(int row_diff)
{
    if(row_diff == 0) return 0;

    if(row_diff > 0)
        nt_cprim_move_cursor_down(row_diff);
    else
        nt_cprim_move_cursor_up(-row_diff);

    cursor_y += row_diff;
    int status = nt_cursor_conform_pos_to_display();
    return status;
}

int nt_cursor_rel_move_xy(int col_diff, int row_diff)
{
    int rel_move_x_status = nt_cursor_rel_move_x(col_diff);
    int rel_move_y_status = nt_cursor_rel_move_y(row_diff);

    return ((rel_move_x_status != 0) || (rel_move_y_status != 0));
}

int nt_cursor_abs_move_to_x(size_t col)
{
    nt_cprim_move_cursor_to_line_col(col + 1, cursor_y + 1); // terminal indexing starts with 1

    cursor_x = col;

    int status = nt_cursor_conform_pos_to_display();
    return status;
}

int nt_cursor_abs_move_to_y(size_t row)
{
    nt_cprim_move_cursor_to_line_col(cursor_x + 1, row + 1); // terminal indexing starts with 1

    cursor_y = row;

    int status = nt_cursor_conform_pos_to_display();
    return status;
}

int nt_cursor_abs_move_to_xy(size_t col, size_t row)
{
    nt_cprim_move_cursor_to_line_col(col + 1, row + 1); // terminal indexing starts with 1

    cursor_x = col;
    cursor_y = row;

    int status = nt_cursor_conform_pos_to_display();
    return status;
}

size_t nt_cursor_get_abs_x()
{
    return cursor_x;
}

size_t nt_cursor_get_abs_y()
{
    return cursor_y;
}

int nt_cursor_conform_pos_to_display()
{
    ssize_t old_cursor_x = cursor_x;
    ssize_t old_cursor_y = cursor_y;

    cursor_x = nt_misc_conform_val(0, cursor_x, nt_display_get_display_width() - 1);
    cursor_y = nt_misc_conform_val(0, cursor_y, nt_display_get_display_height() - 1);

    return ((cursor_x != old_cursor_x) || (cursor_y != old_cursor_y));
}
