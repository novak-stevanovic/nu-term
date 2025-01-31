#ifndef NT_COLOR_H
#define NT_COLOR_H

#include <stddef.h>

#define FORCE_COLOR8_MODE 1

void nt_color_init();

int nt_color_set_fg_color(size_t color_code);
int nt_color_set_bg_color(size_t color_code);

size_t nt_color_get_color_count();

#endif
