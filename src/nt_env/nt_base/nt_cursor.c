#include <stdbool.h>
#include <stdlib.h>

#include "nt_env/base/nt_cursor.h"
#include "internal/nt_primitives.h"
#include "nt_env/nt_display.h"
#include "nt_misc.h"

static size_t cursor_x, cursor_y;
static bool cursor_visible;

// -----------------------------------------------------------------------------------------------------------

void _nt_cursor_init()
{
    nt_cursor_move_home();
    nt_cursor_hide();
}

void _nt_cursor_destroy()
{
    nt_cursor_move_home();
    nt_cursor_show();
}

void nt_cursor_move_home()
{
    nt_prim_cursor_move_home();
    cursor_x = 0;
    cursor_y = 0;
}

void nt_cursor_rel_move_x(ssize_t col_diff)
{
    if(col_diff == 0) return;

    if(col_diff > 0)
        nt_prim_cursor_move_right(col_diff);
    else
        nt_prim_cursor_move_left(-col_diff);

    cursor_x += col_diff;
    nt_cursor_conform_pos_to_display();
}

void nt_cursor_rel_move_y(ssize_t row_diff)
{
    if(row_diff == 0) return;

    if(row_diff > 0)
        nt_prim_cursor_move_down(row_diff);
    else
        nt_prim_cursor_move_up(-row_diff);

    cursor_y += row_diff;
    nt_cursor_conform_pos_to_display();
}

void nt_cursor_rel_move_xy(ssize_t col_diff, ssize_t row_diff)
{
    nt_cursor_rel_move_x(col_diff);
    nt_cursor_rel_move_y(row_diff);
}

void nt_cursor_abs_move_to_x(size_t col)
{
    nt_prim_cursor_move_to_line_col(col + 1, cursor_y + 1); // terminal indexing starts with 1

    cursor_x = col;

    nt_cursor_conform_pos_to_display();
}

void nt_cursor_abs_move_to_y(size_t row)
{
    nt_prim_cursor_move_to_line_col(cursor_x + 1, row + 1); // terminal indexing starts with 1

    cursor_y = row;

    nt_cursor_conform_pos_to_display();
}

void nt_cursor_abs_move_to_xy(size_t col, size_t row)
{
    nt_prim_cursor_move_to_line_col(row + 1, col + 1); // terminal indexing starts with 1

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
    cursor_x = nt_misc_conform_ssize(0, cursor_x, nt_display_get_width() - 1);
    cursor_y = nt_misc_conform_ssize(0, cursor_y, nt_display_get_height() - 1);
}

void nt_cursor_hide()
{
    nt_prim_cursor_hide();
    cursor_visible = false;
}

void nt_cursor_show()
{
    nt_prim_cursor_show();
    cursor_visible = true;
}

bool nt_cursor_is_visible()
{
    return cursor_visible;
}
