#ifndef NT_DRAW_ENGINE_H
#define NT_DRAW_ENGINE_H

#include <stddef.h>

typedef enum { NT_DRAW_ENGINE_HIGH_DRAW_PRIORITY, NT_DRAW_ENGINE_LOW_DRAW_PRIORITY } NTDrawEngineDrawPriority;

struct NTWindow;

void nt_draw_engine_init();

void nt_draw_engine_add_window_to_draw_queue(struct NTWindow* window);
void nt_draw_engine_draw();

size_t nt_draw_engine_calculate_suggested_size(size_t obj_min_size, size_t obj_max_size, size_t obj_pref_size,
        size_t constraint_min_size, size_t constraint_max_size,
        size_t required_size);

#endif
