#include <stdlib.h>
#include <string.h>

#include "nt_core/nt_color.h"
#include "nt_primitives/nt_style_prims.h"

static size_t _color_count = 0;

void nt_color_init()
{
    if(FORCE_COLOR8_MODE) 
        _color_count = 8;
    else
    {
        char *term = getenv("TERM");
        
        if (!term) _color_count = 8;
        if (strstr(term, "256color")) _color_count = 256;
    }
}

int nt_color_set_fg_color(size_t color_code)
{

    if(_color_count == 8)
        nt_sprim_set_fg_color_8(color_code);
    else if(_color_count == 256)
        nt_sprim_set_fg_color_256(color_code);

    return 0;
}

int nt_color_set_bg_color(size_t color_code)
{

    if(_color_count == 8)
        nt_sprim_set_bg_color_8(color_code);
    else if(_color_count == 256)
        nt_sprim_set_bg_color_256(color_code);

    return 0;
}

size_t nt_color_get_color_count()
{
    return _color_count;
}

int nt_color_does_color_exist(size_t color_code)
{
    return color_code < nt_color_get_color_count();
}
