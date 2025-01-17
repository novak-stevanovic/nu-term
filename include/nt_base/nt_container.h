#ifndef NT_CONTAINER_H
#define NT_CONTAINER_H

#include "nt_base/nt_object.h"

struct NTObject;
struct Vector;

struct NTContainer
{
    struct NTObject _base;
};

void nt_container_init(struct NTContainer* container,
        struct NTContainer* parent,
        void (*draw_func)(struct NTObject*, void*),
        struct Vector* (*get_children_func)(struct NTObject*));

#endif
