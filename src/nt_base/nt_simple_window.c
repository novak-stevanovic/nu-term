#include "nt_base/nt_simple_window.h"
#include "nt_base/nt_constraints.h"

static struct NTBaseDrawDataObject* _nt_simple_window_draw_init_func(struct NTObject* simple_window, struct NTConstraints* constraints)
{
    return nt_object_base_draw_data_object_create();
}

static void _nt_simple_window_draw_arrange_func(struct NTObject* window,
        struct NTBaseDrawDataObject* data_object,
        struct NTConstraints* constraints, enum NTDrawMode draw_mode)
{
    data_object->used_x = constraints->_min_width;
    data_object->used_y = constraints->_min_height;
}

void nt_simple_window_init(struct NTSimpleWindow* simple_window,
        struct NTDisplayCell (*window_get_content_at_func)(struct NTWindow* window, size_t x, size_t y),
        NTDrawEngineDrawPriority draw_priority)
{
    struct NTWindow* _simple_window = (struct NTWindow*)simple_window;

    nt_window_init(_simple_window, _nt_simple_window_draw_init_func, _nt_simple_window_draw_arrange_func,
            NULL, NULL, window_get_content_at_func, draw_priority);
}
