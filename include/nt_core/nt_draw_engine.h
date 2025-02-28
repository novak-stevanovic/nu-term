#ifndef NT_DRAW_ENGINE_H
#define NT_DRAW_ENGINE_H

#include "nt_base/nt_object.h"
struct NTWindow;
typedef struct NTWindow NTWindow;

void nt_draw_engine_init();

void nt_draw_engine_add_to_draw_queue(NTWindow* window);
// void nt_draw_engine_draw_all();
//
void nt_draw_engine_draw_object_tree(NTObject* object);

void nt_draw_engine_on_display_size_change();

#endif
