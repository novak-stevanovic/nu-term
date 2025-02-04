#include <stdlib.h>
#include <assert.h>

#include "nt_derived/nt_layout_managers/nt_border_layout_manager.h"
#include "api/nt_vec_api.h"
#include "nt_base/nt_constraints.h"
#include "nt_base/nt_object.h"

void nt_border_layout_manager_init(struct NTBorderLayoutManager* border_layout_manager, struct NTLayoutContainer* layout_container)
{
    nt_layout_manager_init((struct NTLayoutManager*)border_layout_manager,
            _nt_border_layout_manager_arrange_func,
            _nt_border_layout_manager_get_children_func);
}

void _nt_border_layout_manager_arrange_func(struct NTLayoutManager* border_layout_manager, struct NTConstraints* constraints)
{
    assert(border_layout_manager != NULL);
    assert(constraints != NULL);
    assert(nt_constraints_check_consistency(constraints));

    struct NTLayoutContainer* layout_container = nt_layout_manager_get_layout_container(border_layout_manager);
    struct NTObject* _layout_container = (struct NTObject*)layout_container;
    //
    //TODO
    struct NTBorderLayoutManager* _border_layout_manager = (struct NTBorderLayoutManager*)border_layout_manager;

    struct NTObject* north = _border_layout_manager->_north;
    struct NTObject* east = _border_layout_manager->_east;
    struct NTObject* south = _border_layout_manager->_south;
    struct NTObject* west = _border_layout_manager->_west;
    struct NTObject* center = _border_layout_manager->_center;

    struct NTConstraints north_constraints, east_constraints, south_constraints, west_constraints, center_constraints;
    // nt_object_size_constraints_init(&n_constr, constraints->_min_size_x, 0, 
    if(north != NULL)
    {
        // nt_constraints_init(&north_constraints, constraints->_max_size_x, 1, constraints->_max_size_x, constraints->_max_size_y);

        nt_object_draw(north, &north_constraints);
    }
    else
    {
        north_constraints.used_x = 0;
        north_constraints.used_y = 0;
    }
    // TODO -- finish
    //
    // if(east != NULL)
    // {
    //     nt_constraints_init(&east_constraints,
    //             1,
    //             constraints->_max_size_ynorth_constraints
    //             constraints->_max_size_x, 
    //             constraints->_max_size_y);
    //
    //     nt_object_draw(north, &north_constraints);
    // }
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
