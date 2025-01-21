#ifndef NT_CONTAINER_H
#define NT_CONTAINER_H

#include "nt_base/nt_object.h"

struct NTObject;
struct NTObjectBounds;
struct Vector;

struct NTContainer
{
    struct NTObject _base;
};

void nt_container_init(struct NTContainer* container,
        struct NTContainer* parent,
        void (*arrange_content_func)(struct NTObject*, struct NTObjectBounds*),
        struct Vector* (*get_children_func)(const struct NTObject*),
        void (*post_set_size_func)(struct NTObject*));

#endif
