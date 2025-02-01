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
}

void nt_container_set_background(struct NTContainer* container, ssize_t color_code)
{
    assert(container != NULL);

    assert((nt_color_does_color_exist(color_code)) || (color_code == NT_CONTAINER_NO_BACKGROUND));

    if(color_code == NT_CONTAINER_NO_BACKGROUND)
    {
        free(container->_background);
        container->_background = NULL;
    }
    else
    {
        if(container->_background == NULL)
        {
            container->_background = malloc(sizeof(struct NTSolidColorBlock));
            nt_solid_color_block_init(container->_background, color_code);
        }
        else nt_solid_color_block_set_color(container->_background, color_code); //TODO DRAW AGAIN?
    }
}
