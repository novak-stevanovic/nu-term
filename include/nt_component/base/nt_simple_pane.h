#ifndef _NT_SIMPLE_PANE_H_
#define _NT_SIMPLE_PANE_H_

#include "nt_component/base/nt_pane.h"

typedef struct NTSimplePane
{
    NTPane _base;

    nt_abstract void (*_simple_pane_get_cell_at_func)(
            struct NTSimplePane* simple_pane, size_t x, size_t y,
            NTDisplayCell* out_display_cell);

} NTSimplePane;

void nt_simple_pane_init(NTSimplePane* simple_pane, 

        nt_abstract void (*simple_pane_get_cell_at_func)(
            struct NTSimplePane* simple_pane, size_t x, size_t y,
            NTDisplayCell* out_display_cell),

        nt_override void (*object_calculate_content_req_size_func)(
            const NTObject* pane, size_t* out_width, size_t* out_height));

#endif // _NT_SIMPLE_PANE_H_
