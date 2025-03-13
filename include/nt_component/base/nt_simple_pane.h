#ifndef _NT_SIMPLE_PANE_H_
#define _NT_SIMPLE_PANE_H_

#include "nt_component/base/nt_pane.h"

/* NTSimplePane is a specialized pane that computes each cell's content on the fly.
It uses a custom function to determine the draw cell for given coordinates,
making it ideal for simple, static visual effects. */
typedef struct NTSimplePane
{
    NTPane _base;

    /* This function must be overriden by any NTSimplePane concretizations.
     * It must initialize 'out_draw_cell' parameter so that it reflects
     * the content that the NTSimplePane will have at location x, y.
     *
     * For example: a red solid color block would always(no matter the
     * provided x and y parameters) return a draw cell that is red with 
     * no text inside it because it's empty. A half-red, half-blue
     * color block would return a red cell if x < (width / 2) and a blue
     * one otherwise.
     *
     * The NTPane can infer the available space it has _bounds(from NTObject).
     * This simplifies the process of filling the NTPane's _draw_buffer. */
    nt_abstract void (*_simple_pane_get_cell_at_func)(
            struct NTSimplePane* simple_pane, size_t x, size_t y,
            NTDrawCell* out_draw_cell);

} NTSimplePane;

void nt_simple_pane_init(NTSimplePane* simple_pane, 

        nt_abstract void (*simple_pane_get_cell_at_func)(
            struct NTSimplePane* simple_pane, size_t x, size_t y,
            NTDrawCell* out_draw_cell),

        nt_override void (*object_calculate_content_req_size_func)(
            const NTObject* pane, size_t* out_width, size_t* out_height));

#endif // _NT_SIMPLE_PANE_H_
