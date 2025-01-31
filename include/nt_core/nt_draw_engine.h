#ifndef NT_DRAW_ENGINE_H
#define NT_DRAW_ENGINE_H

struct NTWindow;

void nt_draw_engine_init();

void nt_draw_engine_add_window_to_draw_queue(struct NTWindow* window);
void nt_draw_engine_draw();

#endif
