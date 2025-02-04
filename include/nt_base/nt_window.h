#ifndef NT_WINDOW_H
#define NT_WINDOW_H

#include "nt_base/nt_object.h"
#include "nt_core/nt_draw_engine.h"

struct NTDisplayCell;
struct Vector;

/* Represents an abstract window inside this GUI framework. A window is any object that holds actual, drawable information - letters, colored
 * cells... etc.
 * _draw_window_func - This function is called after the window calculates its size. It accepts two parameters - the window width and height.
 *      It is responsible for performing logic that, for example, may position the letters inside the window based on the window size.
 * _calculate_required_size_func - This function is called whenever a window is being drawn, in the first step. The function,
 *      depending on the contents of the window, calculates the size needed to fit ALL of its content inside. The window will then, based on 
 *      the 1. calculated required size, 2. given constraints(usually by the parent), 3. preferred size, calculate its actual size. That size
 *      will be passed to _draw_window_func. Height and width are returned via function parameters.
 * _get_content_at_func - This function returns(through the provided NTDisplayCell buffer) the background color, foreground color and content
 *      of a given cell at coordinates X and Y(arguments). The coordinates are relative to the window's beginning(0, 0). */
struct NTWindow
{
    struct NTObject _base;

    void (*_calculate_required_size_func)(struct NTWindow*, size_t*, size_t*);
    void (*_get_content_at_func)(struct NTWindow*, size_t, size_t, struct NTDisplayCell*);
    void (*_draw_window_func)(struct NTWindow*, size_t, size_t);

    NTDrawEngineDrawPriority _draw_priority; // set priority to NT_DRAW_ENGINE_LOW_DRAW_PRIORITY for drawing windows that are overwritten by
                                             // later drawings of other windows
};

void nt_window_init(struct NTWindow* window,
        void (*calculate_required_size_func)(struct NTWindow*, size_t*, size_t*),
        void (*draw_window_func)(struct NTWindow*, size_t, size_t),
        void (*get_content_at_func)(struct NTWindow*, size_t, size_t, struct NTDisplayCell*),
        NTDrawEngineDrawPriority draw_priority);

void nt_window_get_content_at(struct NTWindow* window, size_t x, size_t y, struct NTDisplayCell* display_cell_buff);

void _nt_window_get_children_func(const struct NTObject* window, struct Vector* vec_buff);

/* NTWindow's implemenation of NTObject's _draw_content_func. This function performs the following:
 * 1. Sets the size(used_x and used_y inside provided constraints) of the window based on: 
 *      A) provided constraints B) inner logic of nt_draw_engine_calculate_suggested_size() C) window's _calculate_required_size_func.
 * 2. Invokes window's _draw_window_func.
 * 3. Invokes nt_draw_engine_add_window_to_draw_queue() to add the window to the drawing queue. */
void _nt_window_draw_content_func(struct NTObject* window, struct NTConstraints* constraints);

#endif
