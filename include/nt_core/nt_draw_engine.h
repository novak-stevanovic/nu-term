#ifndef _NT_DRAW_ENGINE_H_
#define _NT_DRAW_ENGINE_H_

#include <stdbool.h>

struct NTObject;
typedef struct NTObject NTObject;

struct NTPane;
typedef struct NTPane NTPane;

void _nt_draw_engine_init();

void _nt_draw_engine_destruct();

/* Performs a complete redraw of the object tree starting at 'root_object'.
 * This function triggers all necessary rearrangements, recalculations,
 * and drawing operations on the display_buffer, ensuring that the terminal
 * screen reflects the most up-to-date information.
 *
 * If 'root_object' has changed its size, set 'arrange_anchored' to true
 * to adjust any anchored elements accordingly. 
 * This is all done on a separate thread, when all prior requests for drawing
 * are finished. */
void nt_draw_engine_draw_object_tree(NTObject* root_object, bool arrange_anchored);

#endif // _NT_DRAW_ENGINE_H_
