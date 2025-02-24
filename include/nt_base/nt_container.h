#ifndef NT_CONTAINER_H
#define NT_CONTAINER_H

#include "gds_vector.h"
#include "nt_base/nt_object.h"
#include "nt_derived/nt_solid_color_block.h"

struct NTContainer
{
    struct NTObject _base;
    GDSVector _children;
    struct NTSolidColorBlock _background;

    // PART OF OBJECT_DRAW_ARRANGE_FUNC -----------------------------------------------------------

    struct NTObject* (*_container_arrange_get_next_child_func)(struct NTContainer* container,
            struct NTConstraints* constraints,
            struct NTBaseDrawDataObject* draw_data,
            struct NTConstraints* out_child_constraints);
    // returns the next child to draw, its constraints and its starting position.
    // If no space to draw it, return max_size = 0, min_size = 0, start_x = 0, start_y = 0

    void (*_container_arrange_post_draw_child_func)(struct NTContainer* container,
            struct NTObject* child,
            size_t child_width, size_t child_height, 
            struct NTBaseDrawDataObject* draw_data);
    // occurs after drawing of each child. function meant to update 'draw_data' on child draw.

    void (*_container_arrange_conclude_func)(struct NTContainer* container,
            struct NTBaseDrawDataObject* draw_data);
    // finish arranging content. 
    // make sure that draw_data has set its used_width and used_height accordingly.

    // ---------------------------------------------------------------------------------------------

    void (*_container_draw_full_draw_func)(struct NTContainer* container,
            struct NTBaseDrawDataObject* data_object);

};

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
        struct NTBaseDrawDataObject* data_object));

void nt_container_set_background_color(struct NTContainer* container, ssize_t color_code);
ssize_t nt_container_get_background_color(struct NTContainer* container);

GDSVector* nt_container_get_children(struct NTContainer* container);


#endif
