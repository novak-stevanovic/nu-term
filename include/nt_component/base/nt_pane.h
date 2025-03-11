#ifndef _NT_PANE_H_
#define _NT_PANE_H_

#include "nt_component/base/nt_object.h"
#include "nt_shared/nt_draw_buffer.h"

typedef struct NTPane
{
    NTObject _base;
    NTDrawBuffer _draw_buffer;

    nt_abstract void (*_pane_arrange_buffer_func)(struct NTPane* pane);
} NTPane;

void nt_pane_init(NTPane* pane, 

        nt_override void (*pane_arrange_buffer_func)(NTPane* pane),

        nt_override void (*object_calculate_content_req_size_func)(const NTObject* pane,
            size_t* out_width, size_t* out_height));

const NTDrawBuffer* nt_pane_get_draw_buffer(const NTPane* pane);

#endif // _NT_PANE_H_
