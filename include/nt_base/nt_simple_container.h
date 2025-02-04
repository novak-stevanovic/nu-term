#ifndef NT_SIMPLE_CONTAINER_H
#define NT_SIMPLE_CONTAINER_H

#include "nt_base/nt_container.h"

struct Vector;
struct NTConstraints;

struct NTSimpleContainer
{
    struct NTContainer _base;
    struct Vector* _children;
};

void nt_simple_container_init(struct NTSimpleContainer* simple_container,
        void (*arrange_content_func)(struct NTContainer*, struct NTConstraints*));

void _nt_simple_container_get_children_func(const struct NTObject* simple_container, struct Vector* vec_buff);

#endif
