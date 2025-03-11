#ifndef _NT_DISPLAY_H_
#define _NT_DISPLAY_H_

#include <stddef.h>

void nt_display_init();
void nt_display_destruct();

size_t nt_display_get_width();
size_t nt_display_get_height();

#endif // _NT_DISPLAY_H_
