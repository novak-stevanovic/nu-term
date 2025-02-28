#include "nt_core/nt_erase.h"
#include "nt_primitives/nt_erase_prims.h"

void nt_erase_erase_screen()
{
    nt_eprim_erase_screen();
}

void nt_erase_erase_scollback_buffer()
{
    nt_eprim_erase_scrollback_buffer();
}

void nt_erase_erase_line()
{
    nt_eprim_erase_line();
}
