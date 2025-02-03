#ifndef NT_CONTAINER_H
#define NT_CONTAINER_H

#include "nt_base/nt_object.h"
#include "nt_derived/nt_solid_color_block.h"

#define NT_CONTAINER_NO_BACKGROUND -1

struct NTObject;
struct NTObjectSizeConstraints;
struct Vector;

// TODO - wrap arrange_content_func?
struct NTContainer
{
    struct NTObject _base;
    struct NTSolidColorBlock _background;
    void (*_arrange_content_func)(struct NTContainer*, struct NTObjectSizeConstraints*);
};

void nt_container_init(struct NTContainer* container,
        void (*arrange_content_func)(struct NTContainer*, struct NTObjectSizeConstraints*),
        void (*get_children_func)(const struct NTObject*, struct Vector* vec_buff));

void nt_container_set_background(struct NTContainer* container, ssize_t color_code);

void _nt_container_draw_content_func(struct NTObject* container, struct NTObjectSizeConstraints* constraints);

#endif
