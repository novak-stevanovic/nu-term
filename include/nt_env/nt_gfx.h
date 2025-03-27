#ifndef _NT_GFX_H_
#define _NT_GFX_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void _nt_gfx_init();
void _nt_gfx_destroy();

/* Color -------------------------------------------------------------------- */

typedef enum NTColorType { NT_COLOR_COLOR8,
    NT_COLOR_COLOR16,
    NT_COLOR_COLOR256,
    NT_COLOR_TRUECOLOR } NTColorType;

typedef struct NTColor
{
    NTColorType _color_type;

    union {
        uint8_t _color_code;
        struct 
        {
            uint8_t r, g, b;
        } _rgb;
    };
} NTColor;

extern const NTColor NT_COLOR_DEFAULT;

NTColor nt_color_create_c8(uint8_t color_code);
NTColor nt_color_create_c16(uint8_t color_code);
NTColor nt_color_create_c256(uint8_t color_code);
NTColor nt_color_create_tc(uint8_t r, uint8_t g, uint8_t b); // true-color

void nt_color_set_fg(NTColor color);
void nt_color_set_bg(NTColor color);

bool nt_color_are_colors_equal(NTColor color1, NTColor color2);

/* Style -------------------------------------------------------------------- */

typedef uint8_t NTStyle;

extern const NTStyle NT_STYLE_DEFAULT;

#define NT_STYLE_DEFAULT         0
#define NT_STYLE_BOLD            (1 << 0)  // 00000001
#define NT_STYLE_FAINT           (1 << 1)  // 00000010
#define NT_STYLE_ITALIC          (1 << 2)  // 00000100
#define NT_STYLE_UNDERLINE       (1 << 3)  // 00001000
#define NT_STYLE_BLINK           (1 << 4)  // 00010000
#define NT_STYLE_REVERSE         (1 << 5)  // 00100000
#define NT_STYLE_HIDDEN          (1 << 6)  // 01000000
#define NT_STYLE_STRIKETHROUGH   (1 << 7)  // 10000000

void nt_style_set(NTStyle style);

#endif // _NT_GFX_H_
