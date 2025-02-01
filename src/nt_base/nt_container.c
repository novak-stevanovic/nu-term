#include <stdlib.h>
#include <assert.h>

#include "nt_base/nt_container.h"
#include "nt_core/nt_color.h"
#include "nt_derived/nt_solid_color_block.h"

void nt_container_init(struct NTContainer* container,
        void (*draw_content_func)(struct NTObject*, struct NTObjectSizeConstraints* constraints),
        void (*get_children_func)(const struct NTObject*, struct Vector* vec_buff))
{
    assert(container != NULL);
    assert(draw_content_func != NULL);
    assert(get_children_func != NULL);

    nt_object_init((struct NTObject*)container, draw_content_func, get_children_func);

    nt_solid_color_block_init(&container->_background, NT_COLOR_DEFAULT);
}

void nt_container_set_background(struct NTContainer* container, ssize_t color_code)
{
    assert(container != NULL);

    container->_background._color_code = color_code;
    
    // TODO - redraw?
}
