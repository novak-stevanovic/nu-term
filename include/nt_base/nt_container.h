#ifndef NT_CONTAINER_H
#define NT_CONTAINER_H

#include "nt_base/nt_object.h"

struct NTObject;
struct NTObjectSizeConstraints;
struct Vector;

struct NTContainer
{
    struct NTObject _base;
};

void nt_container_init(struct NTContainer* container,
        struct NTContainer* parent,
        void (*arrange_content_func)(struct NTObject*, struct NTObjectSizeConstraints*),
        void (*get_children_func)(const struct NTObject*, struct Vector* vec_buff));

#endif
