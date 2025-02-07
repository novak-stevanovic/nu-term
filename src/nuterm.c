#include "nt_core/nt_color.h"
#include "nt_core/nt_cursor.h"
#include "nt_core/nt_display.h"
#include "nt_log.h"

void nt_init()
{
    nt_display_init();
    nt_cursor_init();
    nt_color_init();
    nt_log_init();
}

void nt_destruct()
{
    nt_log_destruct();
}
