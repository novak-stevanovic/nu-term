#ifndef NT_DISPLAY_H
#define NT_DISPLAY_H

#include <stdio.h>

void nt_display_init();

#define NT_DISPLAY_DEFAULT_COLOR -1
void nt_display_set_bg_color(ssize_t color_code);
void nt_display_set_fg_color(ssize_t color_code);

ssize_t nt_display_get_bg_color();
ssize_t nt_display_get_fg_color();

size_t nt_display_get_display_width();
size_t nt_display_get_display_height();

int nt_display_is_in_bounds(size_t x, size_t y);

#endif
