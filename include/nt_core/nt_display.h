#ifndef NT_DISPLAY_H
#define NT_DISPLAY_H

#include <stdio.h>

struct NTContainer;
typedef struct NTContainer NTContainer;

struct NTObject;
typedef struct NTObject NTObject;

void nt_display_init();

void nt_display_draw_from_root();
void nt_display_set_root(NTObject* new_root);
NTObject* nt_display_get_root();

// ----------------------------------------------------------------

#define NT_DISPLAY_DEFAULT_COLOR -1

size_t nt_display_get_width();
size_t nt_display_get_height();

int nt_display_is_in_bounds(size_t x, size_t y);

#endif
