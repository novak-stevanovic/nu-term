#ifndef NT_SIMPLE_CONTAINER_H
#define NT_SIMPLE_CONTAINER_H

#include "nt_base/nt_container.h"

struct Vector;
struct NTObjectSizeConstraints;

struct NTSimpleContainer
{
    struct NTContainer _base;
    struct Vector* _children;
};

void nt_simple_container_init(struct NTSimpleContainer* simple_container,
        void (*draw_content_func)(struct NTObject*, struct NTObjectSizeConstraints*));

void _nt_simple_container_get_children_func(const struct NTObject* simple_container, struct Vector*);

#endif
