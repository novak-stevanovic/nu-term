#include <stdlib.h>
#include <assert.h>

#include "nt_derived/nt_layout_managers/nt_border_layout_manager.h"
#include "api/nt_vec_api.h"
#include "nt_base/nt_object.h"

void nt_border_layout_manager_init(struct NTBorderLayoutManager* border_layout_manager, struct NTLayoutContainer* layout_container)
{
    nt_layout_manager_init((struct NTLayoutManager*)border_layout_manager,
            layout_container,
            _nt_border_layout_manager_arrange_func,
            _nt_border_layout_manager_get_children_func);
}

void _nt_border_layout_manager_arrange_func(struct NTLayoutManager* border_layout_manager, struct NTObjectSizeConstraints* constraints)
{
    assert(border_layout_manager != NULL);
    assert(constraints != NULL);

    struct NTLayoutContainer* layout_container = nt_layout_manager_get_layout_container(border_layout_manager);
    struct NTObject* _layout_container = (struct NTObject*)layout_container;

    ssize_t pref_size_x = -1;
    ssize_t pref_size_y = -1;

    //TODO
    struct NTBorderLayoutManager* _border_layout_manager = (struct NTBorderLayoutManager*)border_layout_manager;

    struct NTObject* north = _border_layout_manager->_north;
    struct NTObject* east = _border_layout_manager->_east;
    struct NTObject* south = _border_layout_manager->_south;
    struct NTObject* west = _border_layout_manager->_west;
    struct NTObject* center = _border_layout_manager->_center;

    void nt_object_size_constraints_init(struct NTObjectSizeConstraints* constraints,
        ssize_t min_size_x, ssize_t min_size_y,
        ssize_t max_size_x, ssize_t max_size_y);
    // nt_object_size_constraints_init(&n_constr, constraints->_min_size_x, 0, 
    if(north != NULL)
    {

    }
}

void _nt_border_layout_manager_get_children_func(const struct NTLayoutManager* layout_manager, struct Vector* vec_buff)
{
    assert(layout_manager != NULL);
    assert(vec_buff != NULL);

    if(nt_vec_api_vec_get_count(vec_buff) != 0) assert(1 != 1);

    struct NTBorderLayoutManager* border_layout_manager = (struct NTBorderLayoutManager*)layout_manager;

    void* north = border_layout_manager->_north;
    void* east = border_layout_manager->_east;
    void* south = border_layout_manager->_south;
    void* west = border_layout_manager->_west;
    void* center = border_layout_manager->_center;

    if(north != NULL)
        nt_vec_api_vec_append(vec_buff, &north);
    if(east != NULL)
        nt_vec_api_vec_append(vec_buff, &east);
    if(south != NULL)
        nt_vec_api_vec_append(vec_buff, &south);
    if(west != NULL)
        nt_vec_api_vec_append(vec_buff, &west);
    if(center != NULL)
        nt_vec_api_vec_append(vec_buff, &center);
}

struct NTObject* nt_border_layout_manager_get_north(struct NTBorderLayoutManager* border_layout_manager)
{
    assert(border_layout_manager != NULL);

    return border_layout_manager->_north;
}
struct NTObject* nt_border_layout_manager_get_east(struct NTBorderLayoutManager* border_layout_manager)
{
    assert(border_layout_manager != NULL);

    return border_layout_manager->_east;
}

struct NTObject* nt_border_layout_manager_get_south(struct NTBorderLayoutManager* border_layout_manager)
{
    assert(border_layout_manager != NULL);

    return border_layout_manager->_south;
}

struct NTObject* nt_border_layout_manager_get_west(struct NTBorderLayoutManager* border_layout_manager)
{
    assert(border_layout_manager != NULL);

    return border_layout_manager->_west;
}

struct NTObject* nt_border_layout_manager_get_center(struct NTBorderLayoutManager* border_layout_manager)
{
    assert(border_layout_manager != NULL);

    return border_layout_manager->_center;
}

void nt_border_layout_manager_set_north(struct NTBorderLayoutManager* border_layout_manager, struct NTObject* new_north)
{
    assert(border_layout_manager != NULL);

    border_layout_manager->_north = new_north;
}

void nt_border_layout_manager_set_east(struct NTBorderLayoutManager* border_layout_manager, struct NTObject* new_east)
{
    assert(border_layout_manager != NULL);

    border_layout_manager->_east = new_east;
}

void nt_border_layout_manager_set_south(struct NTBorderLayoutManager* border_layout_manager, struct NTObject* new_south)
{
    assert(border_layout_manager != NULL);

    border_layout_manager->_south = new_south;
}

void nt_border_layout_manager_set_west(struct NTBorderLayoutManager* border_layout_manager, struct NTObject* new_west)
{
    assert(border_layout_manager != NULL);

    border_layout_manager->_west = new_west;
}

void nt_border_layout_manager_set_center(struct NTBorderLayoutManager* border_layout_manager, struct NTObject* new_center)
{
    assert(border_layout_manager != NULL);

    border_layout_manager->_center = new_center;
}
