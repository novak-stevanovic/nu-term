#include <assert.h>

#include "nt_base/nt_window.h"
#include "api/nt_vec_api.h"

void nt_window_init(struct NTWindow* window, 
        struct NTContainer* parent,
        void (*draw_content_func)(struct NTObject*, struct NTObjectSizeConstraints*),
        void (*get_content_at_func)(struct NTWindow*, size_t, size_t, struct NTDisplayCell*))
{
    assert(window != NULL);
    assert(get_content_at_func != NULL);

    nt_object_init((struct NTObject*)window, parent, draw_content_func, _nt_window_get_children_func);

    window->_get_content_at_func = get_content_at_func;
}

void nt_window_get_content_at(struct NTWindow* window, size_t x, size_t y, struct NTDisplayCell* display_cell_buff)
{
    assert(window != NULL);
    assert(window->_get_content_at_func != NULL);
    assert(display_cell_buff != NULL);

    window->_get_content_at_func(window, x, y, display_cell_buff);
}

void _nt_window_get_children_func(const struct NTObject* window, struct Vector* vec_buff)
{
    assert(window != NULL);
    assert(vec_buff != NULL);

    assert(nt_vec_api_vec_get_count(vec_buff) == 0);
}
