#ifndef _NT_DRAW_ENGINE_H_
#define _NT_DRAW_ENGINE_H_

#include <stdbool.h>

struct NTObject;
typedef struct NTObject NTObject;

struct NTPane;
typedef struct NTPane NTPane;

void _nt_draw_engine_init();

void _nt_draw_engine_destroy();

void nt_draw_engine_draw_object_tree(NTObject* object);

#endif // _NT_DRAW_ENGINE_H_
