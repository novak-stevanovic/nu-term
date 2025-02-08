#ifndef NT_DRAW_ENGINE_H
#define NT_DRAW_ENGINE_H

#include <stddef.h>

typedef enum { NT_DRAW_ENGINE_HIGH_DRAW_PRIORITY, NT_DRAW_ENGINE_LOW_DRAW_PRIORITY } NTDrawEngineDrawPriority;

struct NTWindow;
struct NTConstraints;

void nt_draw_engine_init();

void nt_draw_engine_add_window_to_draw_queue(struct NTWindow* window);
void nt_draw_engine_draw();

size_t nt_draw_engine_calculate_suggested_size(size_t obj_min_size, size_t obj_max_size, size_t obj_pref_size,
        size_t constraint_min_size, size_t constraint_max_size,
        size_t required_size);

/* Calculates if the object can be drawn in 2D space based on given arguments. It is possible to draw the object if both
 * width and height can be greater than 0. */
int nt_draw_engine_can_object_be_drawn(size_t min_width, size_t min_height, size_t max_width, size_t max_height);

/* Calculates if the object can be drawn in 2D space based on given constraints. It is possible to draw the object if both
 * width and height can be greater than 0.
 * This function only performs a call to nt_draw_engine_can_object_be_drawn() by providing adequate arguments*/
int nt_draw_engine_can_object_be_drawn_constr(struct NTConstraints* constraints);

/* Determines if the object has been drawn based on provided used_x and used_y params. The object is drawn if: both used_x and used_y are
 * greater than 0. This function should be called by providing an object's constraints after nt_object_draw(object). */
int nt_draw_engine_has_object_been_drawn(size_t used_x, size_t used_y);

/* Determines if the object has been drawn based on provided constraints param. The object is drawn if: both used_x and used_y are
 * greater than 0. This function should be called by providing an object's constraints after nt_object_draw(object).
 * The function only performs a call to nt_draw_engine_has_object_been_drawn() by providing adequate arguments. */
int nt_draw_engine_has_object_been_drawn_constr(struct NTConstraints* constraints);

#endif
