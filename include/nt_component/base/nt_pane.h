#ifndef _NT_PANE_H_
#define _NT_PANE_H_

#include "nt_component/base/nt_object.h"
#include "nt_shared/nt_draw_buffer.h"

/* NTPane(derived from NTObject) is a UI element that holds concrete content.
 * Unlike containers, which solely manage and reposition their child objects,
 * an NTPane directly stores displayable content in its NTDrawBuffer.
 * The pane's dedicated arrangement function populates the draw buffer with
 * cell data that reflects the intended visual output. */ 
typedef struct NTPane
{
    NTObject _base;
    NTDrawBuffer _draw_buffer;

    /* This function must be overriden by any NTPane concretizations.
     * It must manipulate the cells inside the _draw_buffer so that they
     * reflect what the pane wants to display on the terminal screen.
     * This _draw_buffer is then, internally, written to the display buffer
     * using NTDisplay's interface.
     * 
     * The NTPane can infer the available space it has _bounds(from NTObject).
     * It must handle the scenario if the available width and/or height are 0. */
    nt_abstract void (*_pane_arrange_buffer_func)(struct NTPane* pane);
} NTPane;

void nt_pane_init(NTPane* pane, 

        nt_override void (*pane_arrange_buffer_func)(NTPane* pane),

        nt_override void (*object_calculate_content_req_size_func)(const NTObject* pane,
            size_t* out_width, size_t* out_height));

NTDrawBuffer* nt_pane_get_draw_buffer(NTPane* pane);

#endif // _NT_PANE_H_
