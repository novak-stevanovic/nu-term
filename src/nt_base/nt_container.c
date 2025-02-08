#include <stdlib.h>
#include <assert.h>

#include "nt_base/nt_container.h"
#include "api/nt_vec_api.h"
#include "nt_base/nt_constraints.h"
#include "nt_core/nt_color.h"
#include "nt_derived/nt_solid_color_block.h"
#include "nt_log.h"

void nt_container_init(struct NTContainer* container,
        void (*arrange_content_func)(struct NTContainer*, struct NTConstraints* constraints),
        void (*get_children_func)(const struct NTObject*, struct Vector* vec_buff))
{
    assert(container != NULL);
    assert(arrange_content_func != NULL);
    assert(get_children_func != NULL);

    nt_object_init((struct NTObject*)container, _nt_container_draw_content_func);

    container->_arrange_content_func = arrange_content_func;

    nt_solid_color_block_init(&container->_background, NT_COLOR_DEFAULT);
    ((struct NTObject*)&container->_background)->_parent = container;
}

void nt_container_set_background_color(struct NTContainer* container, ssize_t color_code)
{
    assert(container != NULL);

    container->_background._color_code = color_code;
    
    // TODO - redraw?
}

ssize_t nt_container_get_background_color(struct NTContainer* container)
{
    assert(container != NULL);

    return container->_background._color_code;
}

void nt_container_get_children(const struct NTContainer* container, struct Vector* vec_buff)
{
    assert(container != NULL);
    assert(vec_buff != NULL);

    container->_get_children_func(container, vec_buff);
}

void _nt_container_non_draw(struct NTContainer* container, struct NTConstraints* constraints)
{
    struct Vector* children_buff = nt_vec_api_vec_create(10, 10, sizeof(struct NTObject*), NULL);
    nt_container_get_children(container, children_buff);

    struct NTObject* curr_child;
    int i;
    struct NTConstraints child_constraints;
    nt_constraints_init(&child_constraints, 0, 0, 0, 0);

    for(i = 0; i < nt_vec_api_vec_get_count(children_buff); i++)
    {
        curr_child = *(struct NTObject**)nt_vec_api_vec_at(children_buff, i);
        assert(curr_child != NULL);
        nt_object_draw(curr_child, &child_constraints);
        _nt_object_set_object_position_based_on_dimensions(curr_child, 0, 0, 0, 0);
    }

    constraints->used_x = constraints->_min_width;
    constraints->used_y = constraints->_min_height;;
}

void _nt_container_draw(struct NTContainer* container, struct NTConstraints* constraints)
{
    assert(container->_arrange_content_func != NULL);
    container->_arrange_content_func(container, constraints);

    struct NTObject* _background = (struct NTObject*)&container->_background;

    struct NTConstraints bg_constraints;
    nt_constraints_init(&bg_constraints, constraints->used_x, constraints->used_y, constraints->used_x, constraints->used_y);

    nt_object_draw(_background, &bg_constraints);

    _nt_object_set_object_position_based_on_dimensions(_background, 0, 0, bg_constraints.used_x, bg_constraints.used_y);
}

void _nt_container_draw_content_func(struct NTObject* container, struct NTConstraints* constraints)
{
    assert(container != NULL);
    assert(constraints != NULL);

    struct NTContainer* _container = (struct NTContainer*)container;

    if(nt_draw_engine_can_object_be_drawn_constr(constraints)) // DRAW
        _nt_container_draw(_container, constraints);
    else                                                       // NOTHING CAN BE DRAWN - constraints are 0, 0
        _nt_container_non_draw(_container, constraints);
}
