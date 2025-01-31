#ifndef TC_DISPLAY_H
#define TC_DISPLAY_H

#include <stddef.h>

void nt_display_init();

size_t nt_display_get_display_width();
size_t nt_display_get_display_height();

int nt_display_is_in_bounds(size_t x, size_t y);

#endif
