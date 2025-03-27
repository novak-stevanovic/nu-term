#include <assert.h>

#include "nt_env/nt_gfx.h"
#include "_nt_primitives.h"

const NTColor NT_COLOR_DEFAULT = {  
    ._color_type = NT_COLOR_COLOR8, ._color_code = 255 };

static NTStyle curr_style;
static NTColor curr_fg_color, curr_bg_color;

void _nt_gfx_init()
{
    nt_prim_gfx_reset();
    curr_style = NT_STYLE_DEFAULT;
    curr_fg_color = NT_COLOR_DEFAULT;
    curr_bg_color = NT_COLOR_DEFAULT;
}

void _nt_gfx_destroy()
{
    nt_prim_gfx_reset();
    curr_bg_color = NT_COLOR_DEFAULT;
    curr_fg_color = NT_COLOR_DEFAULT;
    curr_style = NT_STYLE_DEFAULT;
}

/* Color -------------------------------------------------------------------- */

static void inline _set_fg_nocheck(NTColor color);
static void inline _set_bg_nocheck(NTColor color);

NTColor nt_gfx_color_get_default()
{
    return NT_COLOR_DEFAULT;
}

NTColor nt_color_create_c8(uint8_t color_code)
{
    // TODO: add checks
    return (NTColor) { 
        ._color_type = NT_COLOR_COLOR8,
        ._color_code = color_code 
    };
}

NTColor nt_color_create_c16(uint8_t color_code)
{
    // TODO: add checks

    return (NTColor) { 
        ._color_type = NT_COLOR_COLOR16,
        ._color_code = color_code 
    };
}

NTColor nt_color_create_c256(uint8_t color_code)
{
    // TODO: add checks?

    return (NTColor) { 
        ._color_type = NT_COLOR_COLOR256,
        ._color_code = color_code 
    };
}

NTColor nt_color_create_tc(uint8_t r, uint8_t g, uint8_t b)
{
    return (NTColor) { 
        ._color_type = NT_COLOR_TRUECOLOR,
        ._rgb = { r, g, b }
    };
}

void nt_color_set_fg(NTColor color)
{
    if(nt_color_are_colors_equal(color, curr_fg_color)) return;

    _set_fg_nocheck(color);
}

void nt_color_set_bg(NTColor color)
{
    if(nt_color_are_colors_equal(color, curr_bg_color)) return;

    _set_bg_nocheck(color);
}

NTColor nt_gfx_get_fg_color()
{
    return curr_fg_color;
}

NTColor nt_gfx_get_bg_color()
{
    return curr_bg_color;
}

bool nt_color_are_colors_equal(NTColor color1, NTColor color2)
{
    if(color1._color_type != color2._color_type) return false;

    /* color2's color type is equal to color1's color type */

    if(color1._color_type == NT_COLOR_TRUECOLOR) // if truecolor, compare rgb
    {
        return ((color1._rgb.r == color2._rgb.r) &&
                (color1._rgb.g == color2._rgb.g) &&
                (color1._rgb.b == color2._rgb.b));
    }
    else
        return (color1._color_code == color2._color_code);
}

static void inline _set_fg_nocheck(NTColor color)
{

    if(nt_color_are_colors_equal(color, NT_COLOR_DEFAULT))
        nt_prim_gfx_set_fg_color_default();
    else
    {
        // TODO: add checks?
        if(color._color_type == NT_COLOR_COLOR8)
            nt_prim_gfx_set_fg_color_c8(color._color_code);
        else if(color._color_type == NT_COLOR_COLOR16)
            nt_prim_gfx_set_fg_color_c16(color._color_code);
        else if(color._color_type == NT_COLOR_COLOR256)
            nt_prim_gfx_set_fg_color_c256(color._color_code);
        else // true-color
            nt_prim_gfx_set_fg_color_tc(color._rgb.r, color._rgb.g, color._rgb.b);
    }

    curr_fg_color = color;
}

static void _set_bg_nocheck(NTColor color)
{
    if(nt_color_are_colors_equal(color, NT_COLOR_DEFAULT))
        nt_prim_gfx_set_bg_color_default();
    else
    {
        // TODO: add checks?
        if(color._color_type == NT_COLOR_COLOR8)
            nt_prim_gfx_set_bg_color_c8(color._color_code);
        else if(color._color_type == NT_COLOR_COLOR16)
            nt_prim_gfx_set_bg_color_c16(color._color_code);
        else if(color._color_type == NT_COLOR_COLOR256)
            nt_prim_gfx_set_bg_color_c256(color._color_code);
        else // true-color
            nt_prim_gfx_set_bg_color_tc(color._rgb.r, color._rgb.g, color._rgb.b);
    }

    curr_bg_color = color;
}


/* Style -------------------------------------------------------------------- */

void nt_style_set(NTStyle style)
{
    if(style == curr_style) return;

    /* Complete GFX reset */

    nt_prim_gfx_reset();

    /* Re-enable old colors */

    if(!nt_color_are_colors_equal(curr_fg_color, NT_COLOR_DEFAULT))
        _set_fg_nocheck(curr_fg_color);

    if(!nt_color_are_colors_equal(curr_bg_color, NT_COLOR_DEFAULT))
        _set_bg_nocheck(curr_bg_color);

    /* Set styles */

    if(style == NT_STYLE_DEFAULT) return; // if default - return

    if(style & NT_STYLE_BOLD)
        nt_prim_gfx_set_style(NT_PRIM_GFX_STYLE_BOLD);

    if(style & NT_STYLE_FAINT)
        nt_prim_gfx_set_style(NT_PRIM_GFX_STYLE_FAINT);

    if(style & NT_STYLE_ITALIC)
        nt_prim_gfx_set_style(NT_PRIM_GFX_STYLE_ITALIC);

    if(style & NT_STYLE_UNDERLINE)
        nt_prim_gfx_set_style(NT_PRIM_GFX_STYLE_UNDERLINE);

    if(style & NT_STYLE_BLINK)
        nt_prim_gfx_set_style(NT_PRIM_GFX_STYLE_BLINK);

    if(style & NT_STYLE_REVERSE)
        nt_prim_gfx_set_style(NT_PRIM_GFX_STYLE_REVERSE);

    if(style & NT_STYLE_HIDDEN)
        nt_prim_gfx_set_style(NT_PRIM_GFX_STYLE_HIDDEN);

    if(style & NT_STYLE_STRIKETHROUGH)
        nt_prim_gfx_set_style(NT_PRIM_GFX_STYLE_STRIKETHROUGH);

    curr_style = style;
}

NTStyle nt_gfx_get_style()
{
    return curr_style;
}

