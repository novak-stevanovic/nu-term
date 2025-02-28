#include <stdlib.h>
#include <string.h>

#include "nt_core/nt_color.h"
#include "nt_primitives/nt_style_prims.h"

static size_t _color_count = 0;
static nt_color fg_color = NT_COLOR_DEFAULT;
static nt_color bg_color = NT_COLOR_DEFAULT;

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

void nt_color_set_fg_color(nt_color color)
{
    if(color == fg_color) return;

    if(color == NT_COLOR_DEFAULT) nt_sprim_set_fg_color_default();

    else
    {
        if(_color_count == 8)
            nt_sprim_set_fg_color_8(color);
        else if(_color_count == 256)
            nt_sprim_set_fg_color_256(color);
    }

    fg_color = color;
}

void nt_color_set_bg_color(nt_color color)
{
    if(color == bg_color) return;

    if(color == NT_COLOR_DEFAULT) 
        nt_sprim_set_bg_color_default();

    else
    {
        if(_color_count == 8)
            nt_sprim_set_bg_color_8(color);
        else if(_color_count == 256)
            nt_sprim_set_bg_color_256(color);
    }

    bg_color = color;
}

size_t nt_color_get_color_count()
{
    return _color_count;
}

bool nt_color_does_color_exist(nt_color color)
{
    return color < nt_color_get_color_count();
}

void nt_color_destruct()
{
    nt_color_set_bg_color(NT_COLOR_DEFAULT);
    nt_color_set_fg_color(NT_COLOR_DEFAULT);
}
