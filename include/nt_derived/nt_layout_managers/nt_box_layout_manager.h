#ifndef NT_BOX_LAYOUT_MANAGER_H
#define NT_BOX_LAYOUT_MANAGER_H

#include <stddef.h>

#include "nt_base/nt_layout_manager.h"

typedef enum { NT_BOX_LAYOUT_MANAGER_ORIENTATION_HORIZONTAL, NT_BOX_LAYOUT_MANAGER_ORIENTATION_VERTICAL } NTBoxLayoutManagerOrientation;

struct NTBoxLayoutManager
{
    struct NTLayoutManager _base;

    NTBoxLayoutManagerOrientation _orientation;
    struct Vector* _children;
    size_t _padding, _spacing;
};

void nt_box_layout_manager_init(struct NTBoxLayoutManager* box_layout_manager, NTBoxLayoutManagerOrientation orientation);

void nt_box_layout_manager_set_padding(struct NTBoxLayoutManager* box_layout_manager, size_t padding);
size_t nt_box_layout_manager_get_padding(struct NTBoxLayoutManager* box_layout_manager);

void nt_box_layout_manager_set_spacing(struct NTBoxLayoutManager* box_layout_manager, size_t spacing);
size_t nt_box_layout_manager_get_spacing(struct NTBoxLayoutManager* box_layout_manager);

void _nt_box_layout_manager_arrange_func(struct NTLayoutManager* box_layout_manager, struct NTConstraints* constraints);
void _nt_box_layout_manager_get_children_func(const struct NTLayoutManager* box_layout_manager, struct Vector* vec_buff);

#endif
