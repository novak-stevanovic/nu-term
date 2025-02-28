#ifndef NT_COLOR_H
#define NT_COLOR_H

#include "nt_shared/nt_shared.h"
#include <stdbool.h>
#include <stddef.h>

#define FORCE_COLOR8_MODE 1

void nt_color_init();

nt_color nt_color_get_fg_color();
nt_color nt_color_get_bg_color();

void nt_color_set_fg_color(nt_color color);
void nt_color_set_bg_color(nt_color color);

size_t nt_color_get_color_count();
bool nt_color_does_color_exist(nt_color color);

void nt_color_destruct();

#endif
