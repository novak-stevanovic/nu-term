#ifndef NT_LAYOUT_CONTAINER_H
#define NT_LAYOUT_CONTAINER_H

#include "nt_base/nt_container.h"

struct NTLayoutManager;
struct NTObjectSizeConstraints;
struct Vector;

struct NTLayoutContainer
{
    struct NTContainer _base;
    struct NTLayoutManager* _layout_manager;
};

void nt_layout_container_init(struct NTLayoutContainer* layout_container,
        struct NTContainer* parent,
        struct NTLayoutManager* layout_manager);

struct NTLayoutManager* nt_layout_container_get_layout_manager(struct NTLayoutContainer* layout_container);

void _nt_layout_container_get_children_func(const struct NTObject* layout_container, struct Vector* vec_buff);
void _nt_layout_container_draw_content_func(struct NTObject* layout_container, struct NTObjectSizeConstraints* constraints);


#endif
