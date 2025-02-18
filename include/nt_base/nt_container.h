#ifndef NT_CONTAINER_H
#define NT_CONTAINER_H

#include "gds_vector.h"
#include "nt_base/nt_object.h"
#include "nt_derived/nt_solid_color_block.h"

#define NT_CONTAINER_NO_BACKGROUND -1

struct NTObject;
struct NTConstraints;

/* This structure represents an abstract container in this GUI framework. A container is any NTObject which contains other objects. */
struct NTContainer
{
    struct NTObject _base;
    struct NTSolidColorBlock _background;
    GDSVector _children;

    void* (*_draw_content_init_func)(struct NTContainer* container, struct NTConstraints* constraints);

    struct NTObject* (*_get_next_func)(struct NTContainer* container, struct NTConstraints* constraints,
        struct NTConstraints* child_constraints, void* data);

    void (*_post_draw_child_func)(struct NTContainer* container, struct NTObject* child,
        struct NTConstraints* parent_constraints, struct NTConstraints* child_constraints,
        void* data);

    void (*_conclude_draw_func)(struct NTContainer* container, struct NTConstraints* parent_constraints, void* data);
};

void nt_container_init(struct NTContainer* container,

        void* (*draw_content_init_func)(struct NTContainer* container, struct NTConstraints* constraints),

        struct NTObject* (*get_next_func)(struct NTContainer* container, struct NTConstraints* constraints,
            struct NTConstraints* child_constraints, void* data),

        void (*post_draw_child_func)(struct NTContainer* container, struct NTObject* child,
            struct NTConstraints* parent_constraints, struct NTConstraints* child_constraints,
            void* data),

        void (*conclude_draw_func)(struct NTContainer* container, struct NTConstraints* parent_constraints, void* data));


void nt_container_set_background_color(struct NTContainer* container, ssize_t color_code);
ssize_t nt_container_get_background_color(struct NTContainer* container);

GDSVector* nt_container_get_children(struct NTContainer* container);

/* Implementation for struct NTObject's _draw_content_func field. This is passed as an argument in the nt_container_init() func for the
 * nt_object_init() func. 
 * This function represents an abstraction of the drawing process of ANY container. 
 * 
 * First, a data object is initialized by the container's draw_content_init_func. This data object can hold any information that the
 * specific implementation of this container may use for positioning of its children. For example, a horizontal-box style container might
 * store: count of objects drawn, end coordinates of last drawn object... etc. This information will be available to the container
 * when determining where to place the next child and how much space to give it. 
 *
 * Secondly, a loop is started - as long as there remain undrawn children(while container's get_next_func returns non-NULL), the loop will
 * go on. In the loop, first, the get_next_func() will retrieve the next child that is to be drawn. Also, its min and max constraints will
 * be retrieved. Based on these values, an invocation of nt_object_draw() will be performed. When the child finishes drawing, 
 * a call to container's post_draw_child_func() will be performed. This will happen even if the child is marked as undrawn(used_x, used_y = 0).
 * Here, the container may decide to alter the state of its drawn child by setting its start and end coordinates. The container may also
 * want to increase the drawing count, as well as update the last drawing coordinates(or whatever container-specific information the data
 * object holds). Even when there is no more space left in the container to draw any of its children, the loop will continue. The children
 * are expected to have defined behavior when given min_constraints, max_constraints set to 0.
 *
 * Thirdly, When the loop is terminated, a call to the containers' conclude_draw_func will be performed. This function must, in the case where the
 * children don't occupy enough space(as dictated by container's constraints) collectively, expand the container so it respects the given
 * constraints. The container may also decide to free the initialized data object(by the draw_content_init_func) as it will not be used anymore.
 * The container must also update the constraints' used_x and used_y values(again, so that they fit the given constraints).
 *
 * And finally, a call to an internal function that draws the container's background is performed. This call relies on used_x and used_y 
 * values in provided constraints. */
void _nt_container_draw_content_func(struct NTObject* container, struct NTConstraints* constraints);

#endif
