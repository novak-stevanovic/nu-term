#ifndef NT_LAYOUT_CONTAINER_H
#define NT_LAYOUT_CONTAINER_H

#include "nt_base/nt_container.h"

struct NTLayoutManager;
struct NTConstraints;
struct Vector;

struct NTLayoutContainer
{
    struct NTContainer _base;
    struct NTLayoutManager* _layout_manager;
};

void nt_layout_container_init(struct NTLayoutContainer* layout_container,
        struct NTLayoutManager* layout_manager);

struct NTLayoutManager* nt_layout_container_get_layout_manager(struct NTLayoutContainer* layout_container);

void _nt_layout_container_get_children_func(const struct NTObject* layout_container, struct Vector* vec_buff);
void _nt_layout_container_arrange_content_func(struct NTContainer* layout_container, struct NTConstraints* constraints);


#endif
