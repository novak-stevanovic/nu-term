#ifndef __NT_PRIMITIVES_H__
#define __NT_PRIMITIVES_H__

#include <stddef.h>
#include <stdint.h>

/* Cursor ------------------------------------------------------------------- */

void nt_prim_cursor_move_home();
void nt_prim_cursor_move_to_line_col(size_t line, size_t col);
void nt_prim_cursor_move_up(size_t row_diff);
void nt_prim_cursor_move_down(size_t row_diff);
void nt_prim_cursor_move_right(size_t col_diff);
void nt_prim_cursor_move_left(size_t col_diff);
void nt_prim_cursor_move_to_col(size_t col);

void nt_prim_cursor_hide();
void nt_prim_cursor_show();

/* Screen ------------------------------------------------------------------- */

void nt_prim_screen_erase_screen();
void nt_prim_screen_erase_scrollback_buffer();
void nt_prim_screen_erase_line();
void nt_prim_screen_enable_alt_buffer();
void nt_prim_screen_disable_alt_buffer();

/* GFX ---------------------------------------------------------------------- */

#define NT_PRIM_GFX_STYLE_RESET 0
#define NT_PRIM_GFX_STYLE_BOLD 1
#define NT_PRIM_GFX_STYLE_FAINT 2
#define NT_PRIM_GFX_STYLE_ITALIC 3
#define NT_PRIM_GFX_STYLE_UNDERLINE 4
#define NT_PRIM_GFX_STYLE_BLINK 5
#define NT_PRIM_GFX_STYLE_REVERSE 7
#define NT_PRIM_GFX_STYLE_HIDDEN 8
#define NT_PRIM_GFX_STYLE_STRIKETHROUGH 9

void nt_prim_gfx_reset();

void nt_prim_gfx_set_style(size_t style_code);
// void nt_prim_gfx_reset_style();

void nt_prim_gfx_set_fg_color_c8(uint8_t color_code);
void nt_prim_gfx_set_bg_color_c8(uint8_t color_code);
void nt_prim_gfx_set_fg_color_default();
void nt_prim_gfx_set_bg_color_default();

void nt_prim_gfx_set_fg_color_c16(uint8_t color_code);
void nt_prim_gfx_set_bg_color_c16(uint8_t color_code);

void nt_prim_gfx_set_fg_color_c256(uint8_t color_code);
void nt_prim_gfx_set_bg_color_c256(uint8_t color_code);

// True-color
void nt_prim_gfx_set_fg_color_tc(uint8_t red, uint8_t green, uint8_t blue);
void nt_prim_gfx_set_bg_color_tc(uint8_t red, uint8_t green, uint8_t blue);

#endif // __NT_PRIMITIVES_H__

