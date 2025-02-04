#ifndef NT_CONTAINER_H
#define NT_CONTAINER_H

#include "nt_base/nt_object.h"
#include "nt_derived/nt_solid_color_block.h"

#define NT_CONTAINER_NO_BACKGROUND -1

struct NTObject;
struct NTConstraints;
struct Vector;

/* This structure represents an abstract container in this GUI framework. A container is any NTObject which contains other objects.
 * arrange_content_func is invoked inside the _nt_container_draw_content_func. The former function is responsible for doing the heavy-lifting
 * of the responsibilities an NTContainer has when drawing its content. The container must decide:
 * 1. which children(if any) to draw,
 * 2. drawing positions, size constraints for those children - see more in nt_constrains.h file,
 * 3. it must invoke nt_object_draw(child, child_constraints) for each child that is to be drawn,
 * 4. it must set the position for each child, usually done through _nt_object_set_object_position() function.
 * 5. because the NTContainer is an object, it has to initialize used_x and used_y fields in its constraints argument.
 * Keep in mind that the container decides everything - logic that determines positions and sizes of children, what to do if the whole child
 * cannot be drawn, what to do if there's not enough space even for 1 child...*/
struct NTContainer
{
    struct NTObject _base;
    struct NTSolidColorBlock _background;
    void (*_arrange_content_func)(struct NTContainer*, struct NTConstraints*);
};

void nt_container_init(struct NTContainer* container,
        void (*arrange_content_func)(struct NTContainer*, struct NTConstraints*),
        void (*get_children_func)(const struct NTObject*, struct Vector* vec_buff));

void nt_container_set_background_color(struct NTContainer* container, ssize_t color_code);
ssize_t nt_container_get_background_color(struct NTContainer* container);

/* Implementation for struct NTObject's _draw_content_func field. This is passed as an argument in the nt_container_init() func for the
 * nt_object_init() func. 
 * This function invokes the _arrange_content func of the NTContainer in question. Then it handles background drawing for the NTContainer. */
void _nt_container_draw_content_func(struct NTObject* container, struct NTConstraints* constraints);

#endif
