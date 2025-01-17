#ifndef NT_SIMPLE_CONTAINER_H
#define NT_SIMPLE_CONTAINER_H

#include "nt_base/nt_container.h"

struct Vector;

struct NTSimpleContainer
{
    struct NTContainer _base;
    struct Vector* _children;
};

void nt_simple_container_init(struct NTSimpleContainer* simple_container,
        struct NTContainer* parent,
        void (*_draw_func)(struct NTObject*, void*));

struct Vector* _nt_simple_container_get_children_func(struct NTObject* simple_container);

#endif
