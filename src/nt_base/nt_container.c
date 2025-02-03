#include <stdlib.h>
#include <assert.h>

#include "nt_base/nt_container.h"
#include "nt_core/nt_color.h"
#include "nt_derived/nt_solid_color_block.h"

void nt_container_init(struct NTContainer* container,
        void (*arrange_content_func)(struct NTContainer*, struct NTObjectSizeConstraints* constraints),
        void (*get_children_func)(const struct NTObject*, struct Vector* vec_buff))
{
    assert(container != NULL);
    assert(arrange_content_func != NULL);
    assert(get_children_func != NULL);

    nt_object_init((struct NTObject*)container, _nt_container_draw_content_func, get_children_func);

    container->_arrange_content_func = arrange_content_func;

    nt_solid_color_block_init(&container->_background, NT_COLOR_DEFAULT);
    ((struct NTObject*)&container->_background)->_parent = container;
}

void nt_container_set_background(struct NTContainer* container, ssize_t color_code)
{
    assert(container != NULL);

    container->_background._color_code = color_code;
    
    // TODO - redraw?
}

void _nt_container_draw_content_func(struct NTObject* container, struct NTObjectSizeConstraints* constraints)
{
    assert(container != NULL);
    assert(constraints != NULL);

    struct NTContainer* _container = (struct NTContainer*)container;

    assert(_container->_arrange_content_func != NULL);
    _container->_arrange_content_func(_container, constraints);

    struct NTObject* _background = (struct NTObject*)&_container->_background;

    struct NTObjectSizeConstraints bg_constraints;
    nt_object_size_constraints_init(&bg_constraints, constraints->used_x, constraints->used_y, constraints->used_x, constraints->used_y);
    nt_object_draw(_background, &bg_constraints);

    _background->_rel_end_x = constraints->used_x;
    _background->_rel_end_y = constraints->used_y;
}
