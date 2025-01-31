#include "nt_core/nt_color.h"
#include "nt_core/nt_cursor.h"
#include "nt_core/nt_display.h"

void nt_init()
{
    nt_display_init();
    nt_cursor_init();
    nt_color_init();
}
