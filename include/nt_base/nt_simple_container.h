#ifndef NT_SIMPLE_CONTAINER_H
#define NT_SIMPLE_CONTAINER_H

#include "nt_base/nt_container.h"

struct Vector;
struct NTObjectBounds;

struct NTSimpleContainer
{
    struct NTContainer _base;
    struct Vector* _children;
};

void nt_simple_container_init(struct NTSimpleContainer* simple_container,
        struct NTContainer* parent,
        void (*arrange_content_func)(struct NTObject*, struct NTObjectBounds*),
        void (*post_set_size_func)(struct NTObject*));

struct Vector* _nt_simple_container_get_children_func(const struct NTObject* simple_container);

#endif
