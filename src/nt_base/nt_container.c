#include <stdlib.h>
#include <assert.h>

#include "nt_base/nt_container.h"
#include "nt_base/nt_constraints.h"
#include "nt_core/nt_color.h"
#include "nt_derived/nt_solid_color_block.h"
#include "nt_log.h"

// -------------------------------------------------------------------------------------------------------------------------------

void nt_container_init(struct NTContainer* container,

        void* (*draw_content_init_func)(struct NTContainer* container, struct NTConstraints* constraints),

        struct NTObject* (*get_next_func)(struct NTContainer* container, struct NTConstraints* constraints,
            struct NTConstraints* child_constraints, void* data),

        void (*post_draw_child_func)(struct NTContainer* container, struct NTObject* child,
            struct NTConstraints* parent_constraints, struct NTConstraints* child_constraints,
            void* data),

        void (*conclude_draw_func)(struct NTContainer* container, struct NTConstraints* parent_constraints, void* data))
{
    assert(container != NULL);

    nt_object_init((struct NTObject*)container, _nt_container_draw_content_func);

    container->_draw_content_init_func = draw_content_init_func;
    container->_get_next_func = get_next_func;
    container->_post_draw_child_func = post_draw_child_func;
    container->_conclude_draw_func = conclude_draw_func;

    nt_solid_color_block_init_background(&container->_background, 7);
    gds_vector_init_default(&container->_children, sizeof(void*));

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

GDSVector* nt_container_get_children(struct NTContainer* container)
{
    assert(container != NULL);

    return &container->_children;
}

void _nt_container_draw_background(struct NTContainer* container, size_t width, size_t height)
{
    struct NTObject* _background = (struct NTObject*)&container->_background;
    struct NTConstraints bg_constraints;
    nt_constraints_init(&bg_constraints, width, height, width, height);
    nt_object_draw(_background, &bg_constraints);
    _nt_object_set_object_position_based_on_dimensions(_background, 0, 0, bg_constraints._used_x, bg_constraints._used_y);
}

void _nt_container_draw_content_func(struct NTObject* container, struct NTConstraints* constraints)
{
    assert(container != NULL);
    assert(constraints != NULL);

    struct NTContainer* _container = (struct NTContainer*)container;

    void* data_obj = _container->_draw_content_init_func(_container, constraints);

    struct NTObject* curr_child = NULL;
    struct NTConstraints child_constraints;
    while((curr_child = _container->_get_next_func(_container, constraints, &child_constraints, data_obj)))
    {
        nt_object_draw(curr_child, &child_constraints);

        _container->_post_draw_child_func(_container, curr_child, constraints, &child_constraints, data_obj);

    }

    _container->_conclude_draw_func(_container, constraints, data_obj);

    _nt_container_draw_background(_container, constraints->_used_x, constraints->_used_y);
}

// -------------------------------------------------------------------------------------------------------------------------------

static void* _nt_container_draw_content_init(struct NTContainer* container, struct NTConstraints* constraints)
{
    assert(container != NULL);
    assert(constraints != NULL);

    assert(container->_draw_content_init_func != NULL);
    return container->_draw_content_init_func(container, constraints);
}

static struct NTObject* _nt_container_get_next(struct NTContainer* container, struct NTConstraints* constraints,
        struct NTConstraints* child_constraints, void* data)
{
    assert(container != NULL);
    assert(constraints != NULL);

    assert(container->_get_next_func != NULL);

    return container->_get_next_func(container, constraints, child_constraints, data);
}

static void _post_draw_child_func(struct NTContainer* container, struct NTObject* child,
        struct NTConstraints* parent_constraints, struct NTConstraints* child_constraints,
        void* data)
{
    assert(container != NULL);
    assert(child != NULL);
    assert(parent_constraints != NULL);
    assert(child_constraints != NULL);
    assert(data != NULL);

    if(container->_post_draw_child_func) 
        container->_post_draw_child_func(container, child, parent_constraints, child_constraints, data);
}

static void _nt_container_conclude_draw(struct NTContainer* container, struct NTConstraints* parent_constraints, void* data)
{
    assert(container != NULL);
    assert(parent_constraints != NULL);
    assert(data != NULL);

    if(container->_conclude_draw_func) container->_conclude_draw_func(container, parent_constraints, data);
}
