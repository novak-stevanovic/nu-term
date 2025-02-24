#ifndef NT_DISPLAY_H
#define NT_DISPLAY_H

#include <stdio.h>

struct NTContainer;
struct NTObject;

enum NTRootDrawOptimization { NT_ROOT_DRAW_OPTIMIZED, NT_ROOT_DRAW_UNOPTIMIZED };

void nt_display_init();

void nt_display_draw_from_root(enum NTRootDrawOptimization draw_optimization);
void nt_display_set_root(struct NTObject* new_root);
struct NTObject* nt_display_get_root();

// ----------------------------------------------------------------

#define NT_DISPLAY_DEFAULT_COLOR -1

size_t nt_display_get_display_width();
size_t nt_display_get_display_height();

int nt_display_is_in_bounds(size_t x, size_t y);

#endif
