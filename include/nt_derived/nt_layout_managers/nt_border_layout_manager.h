#ifndef NT_BORDER_LAYOUT_MANAGER_H
#define NT_BORDER_LAYOUT_MANAGER_H

#include "nt_base/nt_layout_manager.h"

struct Vector;

struct NTBorderLayoutManager
{
    struct NTLayoutManager _base;

    struct NTObject *_north, *_east, *_south, *_west, *_center;
};

void nt_border_layout_manager_init(struct NTBorderLayoutManager* border_layout_manager, struct NTLayoutContainer* layout_container);

void _nt_border_layout_manager_arrange_func(struct NTLayoutManager* border_layout_manager, struct NTObjectSizeConstraints* constraints); 
void _nt_border_layout_manager_get_children_func(const struct NTLayoutManager* layout_manager, struct Vector* vec_buff);

struct NTObject* nt_border_layout_manager_get_north(struct NTBorderLayoutManager* border_layout_manager);
struct NTObject* nt_border_layout_manager_get_east(struct NTBorderLayoutManager* border_layout_manager);
struct NTObject* nt_border_layout_manager_get_south(struct NTBorderLayoutManager* border_layout_manager);
struct NTObject* nt_border_layout_manager_get_west(struct NTBorderLayoutManager* border_layout_manager);
struct NTObject* nt_border_layout_manager_get_center(struct NTBorderLayoutManager* border_layout_manager);

void nt_border_layout_manager_set_north(struct NTBorderLayoutManager* border_layout_manager, struct NTObject* new_north);
void nt_border_layout_manager_set_east(struct NTBorderLayoutManager* border_layout_manager, struct NTObject* new_east);
void nt_border_layout_manager_set_south(struct NTBorderLayoutManager* border_layout_manager, struct NTObject* new_south);
void nt_border_layout_manager_set_west(struct NTBorderLayoutManager* border_layout_manager, struct NTObject* new_west);
void nt_border_layout_manager_set_center(struct NTBorderLayoutManager* border_layout_manager, struct NTObject* new_center);

#endif
