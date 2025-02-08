#ifndef NT_BOX_LAYOUT_MANAGER_H
#define NT_BOX_LAYOUT_MANAGER_H

#include <stddef.h>

#include "nt_base/nt_layout_manager.h"
#include "nt_shared/nt_padding_object.h"

typedef enum { NT_BOX_LAYOUT_MANAGER_ORIENTATION_HORIZONTAL, NT_BOX_LAYOUT_MANAGER_ORIENTATION_VERTICAL } NTBoxLayoutManagerOrientation;

struct NTObject;

struct NTBoxLayoutManager
{
    struct NTLayoutManager _base;

    NTBoxLayoutManagerOrientation _orientation;
    struct Vector* _children;
    size_t _spacing;
    struct NTPaddingObject _padding;
};

void nt_box_layout_manager_init(struct NTBoxLayoutManager* box_layout_manager, NTBoxLayoutManagerOrientation orientation);

void nt_box_layout_manager_add_child(struct NTBoxLayoutManager* box_layout_manager, struct NTObject* object);

void nt_box_layout_manager_set_spacing(struct NTBoxLayoutManager* box_layout_manager, size_t spacing);
size_t nt_box_layout_manager_get_spacing(struct NTBoxLayoutManager* box_layout_manager);

void _nt_box_layout_manager_arrange_func(struct NTLayoutManager* box_layout_manager, struct NTConstraints* constraints);
void _nt_box_layout_manager_get_children_func(const struct NTLayoutManager* box_layout_manager, struct Vector* vec_buff);

#endif
