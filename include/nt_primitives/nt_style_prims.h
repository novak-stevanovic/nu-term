#ifndef NT_STYLE_PRIMS_H
#define NT_STYLE_PRIMS_H

#include <stddef.h>

// RESET
#define NT_SPRIM_GFX_RESET_CODE "\e[0m"

#define NT_SPRIM_SET_STYLE_MODE_CODE "\e[%ldm"
#define NT_SPRIM_RESET_STYLE_MODE_CODE "\e[2%ldm"

#define _NT_SPRIM_SET_BOLD_MODE_CODE_VAL 1
#define _NT_SPRIM_RESET_BOLD_MODE_CODE_VAL 2
#define _NT_SPRIM_SET_DIM_MODE_CODE_VAL 2
#define _NT_SPRIM_RESET_DIM_MODE_CODE_VAL 2
#define _NT_SPRIM_SET_ITALIC_MODE_CODE_VAL 3
#define _NT_SPRIM_RESET_ITALIC_MODE_CODE_VAL 3
#define _NT_SPRIM_SET_UNDERLINE_MODE_CODE_VAL 4
#define _NT_SPRIM_RESET_UNDERLINE_MODE_CODE_VAL 4
#define _NT_SPRIM_SET_BLINK_MODE_CODE_VAL 5
#define _NT_SPRIM_RESET_BLINK_MODE_CODE_VAL 5
#define _NT_SPRIM_SET_INVERSE_MODE_CODE_VAL 7
#define _NT_SPRIM_RESET_INVERSE_MODE_CODE_VAL 7
#define _NT_SPRIM_SET_HIDDEN_MODE_CODE_VAL 8
#define _NT_SPRIM_RESET_HIDDEN_MODE_CODE_VAL 8
#define _NT_SPRIM_SET_STRIKETHROUGH_MODE_CODE_VAL 9
#define _NT_SPRIM_RESET_STRIKETHROUGH_MODE_CODE_VAL 9

#define NT_SPRIM_SET_FG_COLOR_CODE_C8 "\e[3%ldm"
#define NT_SPRIM_SET_BG_COLOR_CODE_C8 "\e[4%ldm"
//TODO
// #define _NT_SPRIM_SET_FG_DEFAULT_COLOR_CODE_VAL ((size_t)9)
// #define _NT_SPRIM_SET_BG_DEFAULT_COLOR_CODE_VAL ((size_t)9)

#define NT_SPRIM_SET_FG_COLOR_CODE_C256 "\e[38;5;%ldm"
#define NT_SPRIM_SET_BG_COLOR_CODE_C256 "\e[48;5;%ldm"

void nt_sprim_gfx_reset();

void nt_sprim_set_style_mode(size_t set_style_code);
void nt_sprim_reset_style_mode(size_t reset_style_code);

void nt_sprim_set_fg_color_8(size_t color_code);
void nt_sprim_set_bg_color_8(size_t color_code);

void nt_sprim_set_fg_color_256(size_t color_code);
void nt_sprim_set_bg_color_256(size_t color_code);

//TODO
// void nt_sprim_set_default_fg_color();
// void nt_sprim_set_default_bg_color();

#endif
