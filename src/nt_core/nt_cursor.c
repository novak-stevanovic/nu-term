#include <stdbool.h>
#include <stdlib.h>

#include "nt_core/nt_cursor.h"
#include "nt_core/nt_display.h"
#include "nt_misc.h"
#include "nt_primitives/nt_cursor_prims.h"

ssize_t cursor_x, cursor_y;
bool cursor_visible;

// ------------------------------------------------------------------------------------------------------------

void nt_cursor_init()
{
    nt_cprim_move_cursor_home();
    cursor_x = 0;
    cursor_y = 0;

    nt_cursor_hide();
}

void nt_cursor_rel_move_x(int col_diff)
{
    if(col_diff == 0) return;

    if(col_diff > 0)
        nt_cprim_move_cursor_right(col_diff);
    else
        nt_cprim_move_cursor_left(-col_diff);

    cursor_x += col_diff;
    nt_cursor_conform_pos_to_display();
}

void nt_cursor_rel_move_y(int row_diff)
{
    if(row_diff == 0) return; 

    if(row_diff > 0)
        nt_cprim_move_cursor_down(row_diff);
    else
        nt_cprim_move_cursor_up(-row_diff);

    cursor_y += row_diff;
    nt_cursor_conform_pos_to_display();
}

void nt_cursor_rel_move_xy(int col_diff, int row_diff)
{
    nt_cursor_rel_move_x(col_diff);
    nt_cursor_rel_move_y(row_diff);
}

void nt_cursor_abs_move_to_x(size_t col)
{
    nt_cprim_move_cursor_to_line_col(col + 1, cursor_y + 1); // terminal indexing starts with 1

    cursor_x = col;

    nt_cursor_conform_pos_to_display();
}

void nt_cursor_abs_move_to_y(size_t row)
{
    nt_cprim_move_cursor_to_line_col(cursor_x + 1, row + 1); // terminal indexing starts with 1

    cursor_y = row;

    nt_cursor_conform_pos_to_display();
}

void nt_cursor_abs_move_to_xy(size_t col, size_t row)
{
    nt_cprim_move_cursor_to_line_col(row + 1, col + 1); // terminal indexing starts with 1

    cursor_x = col;
    cursor_y = row;

    nt_cursor_conform_pos_to_display();
}

size_t nt_cursor_get_abs_x()
{
    return cursor_x;
}

size_t nt_cursor_get_abs_y()
{
    return cursor_y;
}

void nt_cursor_conform_pos_to_display()
{
    cursor_x = nt_misc_conform_val(0, cursor_x, nt_display_get_width() - 1);
    cursor_y = nt_misc_conform_val(0, cursor_y, nt_display_get_height() - 1);
}

void nt_cursor_hide()
{
    nt_cprim_hide_cursor();
    cursor_visible = false;
}

void nt_cursor_show()
{
    nt_cprim_show_cursor();
    cursor_visible = true;
}

void nt_cursor_destruct()
{
    nt_cursor_abs_move_to_xy(0, 0);
    nt_cursor_show();
}
