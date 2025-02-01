#include "nt_core/nt_erase.h"
#include "nt_core/nt_color.h"
#include "nt_primitives/nt_erase_prims.h"
#include "nt_primitives/nt_style_prims.h"

void nt_erase_erase_screen(ssize_t color_code)
{
    if(color_code == NT_COLOR_DEFAULT)
        nt_sprim_gfx_reset();
    else
        nt_color_set_bg_color(color_code);

    nt_eprim_erase_screen();

}
void nt_erase_erase_line(ssize_t color_code)
{
    if(color_code == NT_COLOR_DEFAULT)
        nt_sprim_gfx_reset();
    else
        nt_color_set_bg_color(color_code);

    nt_eprim_erase_line();
}
