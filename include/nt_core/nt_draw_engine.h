#ifndef NT_DRAW_ENGINE_H
#define NT_DRAW_ENGINE_H

#include <stddef.h>
enum NTRootDrawOptimization;

typedef enum { NT_DRAW_ENGINE_HIGH_DRAW_PRIORITY, NT_DRAW_ENGINE_LOW_DRAW_PRIORITY } NTDrawEngineDrawPriority;

struct NTWindow;

void nt_draw_engine_init();

void nt_draw_engine_add_window_to_draw_queue(struct NTWindow* window);
void nt_draw_engine_draw(enum NTRootDrawOptimization draw_optimization);
void nt_draw_engine_stop_draw();

void nt_draw_engine_on_display_size_change();


#endif
