#include "nt_base/nt_container.h"
#include "nt_base/nt_constraints.h"

static void _object_draw_arrange_func(struct NTObject* container, 
        struct NTBaseDrawDataObject* data_object,
        struct NTConstraints* constraints, enum NTDrawMode draw_mode);

static void _object_draw_full_draw_func(struct NTObject* container, 
        struct NTBaseDrawDataObject* data_object);

// ----------------------------------------------------------------------------------

void nt_container_init(struct NTContainer* container,

    struct NTBaseDrawDataObject* (*object_draw_init_func)(struct NTObject* container,
        struct NTConstraints* constraints),

    struct NTObject* (*container_arrange_get_next_child_func)(struct NTContainer* container,
        struct NTConstraints* constraints,
        struct NTBaseDrawDataObject* draw_data,
        struct NTConstraints* out_child_constraints),

    void (*container_arrange_post_draw_child_func)(struct NTContainer* container,
        struct NTObject* child,
        size_t child_width, size_t child_height,
        struct NTBaseDrawDataObject* draw_data),

    void (*container_arrange_conclude_func)(struct NTContainer* container,
        struct NTBaseDrawDataObject* draw_data),

    void (*container_draw_full_draw_func)(struct NTContainer* container,
            struct NTBaseDrawDataObject* data_object),

    void (*object_conclude_draw_func)(struct NTObject* container,
        struct NTBaseDrawDataObject* data_object))

{
    nt_object_init((struct NTObject*)container,
            object_draw_init_func,
            _object_draw_arrange_func,
            _object_draw_full_draw_func,
            object_conclude_draw_func);

    container->_container_arrange_get_next_child_func = container_arrange_get_next_child_func;
    container->_container_arrange_post_draw_child_func = container_arrange_post_draw_child_func;
    container->_container_arrange_conclude_func = container_arrange_conclude_func;
    container->_container_draw_full_draw_func = container_draw_full_draw_func;

    gds_vector_init_default(&container->_children, sizeof(void*));
    nt_solid_color_block_init(&container->_background, 9, NT_DRAW_ENGINE_LOW_DRAW_PRIORITY);
}

// ----------------------------------------------------------------------------------

void _object_draw_arrange_func(struct NTObject* container, 
        struct NTBaseDrawDataObject* data_object,
        struct NTConstraints* constraints, enum NTDrawMode draw_mode)
{
    struct NTContainer* _container = (struct NTContainer*)container;

    struct NTConstraints child_constraints;

    struct NTObject* next_child;
    size_t child_used_width, child_used_height;
    if(_container->_container_arrange_get_next_child_func != NULL)
    {
        while(1)
        {
            next_child = _container->_container_arrange_get_next_child_func(_container,
                    constraints, data_object, &child_constraints);

            if(next_child == NULL) break;
            // else

            nt_object_draw(next_child, &child_constraints,
                    draw_mode, &child_used_width, &child_used_height);

            _container->_container_arrange_post_draw_child_func(_container, next_child,
                    child_used_width, child_used_height, data_object);
        }
    }

    if(_container->_container_arrange_conclude_func != NULL) 
        _container->_container_arrange_conclude_func(_container, data_object);
}

void _object_draw_full_draw_func(struct NTObject* container, 
        struct NTBaseDrawDataObject* data_object)
{
    struct NTContainer* _container = (struct NTContainer*)container;

    nt_object_set_object_position_based_on_dimensions((struct NTObject*)&_container->_background,
            0, 0, data_object->used_x, data_object->used_y);

    nt_draw_engine_add_window_to_draw_queue((struct NTWindow*)&_container->_background);

    _container->_container_draw_full_draw_func(_container, data_object);
}

void nt_container_set_background_color(struct NTContainer* container, ssize_t color_code)
{
    // TODO redraw
    nt_solid_color_block_set_color(&container->_background, color_code);
}

ssize_t nt_container_get_background_color(struct NTContainer* container)
{
    return nt_solid_color_block_get_color(&container->_background);
}

GDSVector* nt_container_get_children(struct NTContainer* container)
{
    return &container->_children;
}

