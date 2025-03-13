#include "nt_env/base/nt_screen.h"
#include "internal/nt_primitives.h"

void _nt_screen_init()
{
    // nt_screen_erase_screen();
    nt_screen_enable_alternate_buffer();
}

void _nt_screen_destruct()
{
    // nt_screen_erase_screen();
    nt_screen_disable_alternate_buffer();
}

void nt_screen_erase_screen()
{
    nt_prim_screen_erase_screen();
}

void nt_screen_erase_scrollback_buffer()
{
    nt_prim_screen_erase_scrollback_buffer();
}

void nt_screen_erase_line()
{
    nt_prim_screen_erase_line();
}

void nt_screen_enable_alternate_buffer()
{
    nt_prim_screen_enable_alt_buffer();
}

void nt_screen_disable_alternate_buffer()
{
    nt_prim_screen_disable_alt_buffer();
}
