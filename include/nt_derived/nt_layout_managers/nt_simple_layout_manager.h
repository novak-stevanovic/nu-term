#ifndef NT_SIMPLE_LAYOUT_MANAGER_H
#define NT_SIMPLE_LAYOUT_MANAGER_H

#include "nt_base/nt_layout_manager.h"
#include "nt_shared/nt_padding_object.h"

struct NTSimpleLayoutManager
{
    struct NTLayoutManager _base;

    struct NTPaddingObject _padding_object;
    struct NTObject* _child;
};

void nt_simple_layout_manager_init(struct NTSimpleLayoutManager* simple_layout_manager);

void _nt_simple_layout_manager_arrange_func(struct NTLayoutManager* simple_layout_manager, struct NTConstraints* constraints);
void _nt_simple_layout_manager_get_children_func(const struct NTLayoutManager* simple_layout_manager , struct Vector* vec_buff);

struct NTObject* nt_simple_layout_manager_get_child(const struct NTSimpleLayoutManager* simple_layout_manager);
void nt_simple_layout_manager_set_container_child(struct NTSimpleLayoutManager* simple_layout_manager, struct NTObject* object); // TODO

#endif
