#ifndef NT_LAYOUT_CONTAINER_H
#define NT_LAYOUT_CONTAINER_H

#include "nt_base/nt_container.h"

struct NTLayoutManager;
struct NTConstraints;
struct Vector;

/* A layout container is a structure that represents a container which manages its children by delegating that work to a NTLayoutManager. */
struct NTLayoutContainer
{
    struct NTContainer _base;
    struct NTLayoutManager* _layout_manager;
};

void nt_layout_container_init(struct NTLayoutContainer* layout_container);

void nt_layout_container_set_layout_manager(struct NTLayoutContainer* layout_container, struct NTLayoutManager* layout_manager);
struct NTLayoutManager* nt_layout_container_get_layout_manager(struct NTLayoutContainer* layout_container);

void _nt_layout_container_get_children_func(const struct NTObject* layout_container, struct Vector* vec_buff);
/* NTLayoutContainer's implementation of NTContainer's _arrange_content_func. This function invokes the _layout_manager->_arrange func. */
void _nt_layout_container_arrange_content_func(struct NTContainer* layout_container, struct NTConstraints* constraints);

#endif
