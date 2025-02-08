#include <stdlib.h>
#include <assert.h>

#include "nt_derived/nt_layout_managers/nt_box_layout_manager.h"
#include "api/nt_vec_api.h"
#include "nt_base/nt_constraints.h"
#include "nt_base/nt_object.h"
#include "nt_core/nt_draw_engine.h"
#include "nt_log.h"
#include "nt_misc.h"

void nt_box_layout_manager_init(struct NTBoxLayoutManager* box_layout_manager, NTBoxLayoutManagerOrientation orientation)
{
    assert(box_layout_manager != NULL);

    nt_layout_manager_init((struct NTLayoutManager*)box_layout_manager,
            _nt_box_layout_manager_arrange_func,
            _nt_box_layout_manager_get_children_func);

    box_layout_manager->_orientation = orientation;
    nt_padding_object_init(&box_layout_manager->_padding);
    box_layout_manager->_spacing = 0;

    box_layout_manager->_children = nt_vec_api_vec_create(10, 10, sizeof(void*), NULL);
}

void nt_box_layout_manager_add_child(struct NTBoxLayoutManager* box_layout_manager, struct NTObject* object)
{
    assert(box_layout_manager != NULL);
    assert(object != NULL);

    nt_vec_api_vec_append(box_layout_manager->_children, &object);
}

void nt_box_layout_manager_set_spacing(struct NTBoxLayoutManager* box_layout_manager, size_t spacing)
{
    assert(box_layout_manager != NULL);

    box_layout_manager->_spacing = spacing;

    //TODO -- redraw?
}

size_t nt_box_layout_manager_get_spacing(struct NTBoxLayoutManager* box_layout_manager)
{
    assert(box_layout_manager != NULL);

    return box_layout_manager->_spacing;
}

int _get_next(struct NTBoxLayoutManager* box_layout_manager,
        ssize_t* next_start_x, ssize_t* next_start_y,
        struct NTConstraints* next_constraints, struct NTConstraints* parent_constraints)
{
    assert(box_layout_manager != NULL);
    assert(next_start_x != NULL);
    assert(next_start_y != NULL);
    assert(next_constraints != NULL);
    assert(parent_constraints != NULL);

    next_constraints->_min_height = 0;
    next_constraints->_min_width = 0;

    ssize_t parent_constr_max_width = (ssize_t)parent_constraints->_max_width;
    ssize_t parent_constr_max_height = (ssize_t)parent_constraints->_max_height;

    ssize_t padding_north = (ssize_t)box_layout_manager->_padding.north;
    ssize_t padding_south = (ssize_t)box_layout_manager->_padding.south;
    ssize_t padding_east = (ssize_t)box_layout_manager->_padding.east;
    ssize_t padding_west = (ssize_t)box_layout_manager->_padding.west;
    ssize_t spacing = (ssize_t)box_layout_manager->_spacing;

    if(box_layout_manager->_orientation == NT_BOX_LAYOUT_MANAGER_ORIENTATION_HORIZONTAL)
    {
        next_constraints->_max_height = nt_misc_max(0, parent_constr_max_height - padding_south - padding_north);

        if(*next_start_x == -1)
        {
            *next_start_x = padding_west;
            *next_start_y = padding_north;

            next_constraints->_max_width = nt_misc_max(0, parent_constr_max_width - padding_east - padding_west);
        }
        else
        {
            *next_start_x += spacing;
            *next_start_y = padding_north;

            next_constraints->_max_width = nt_misc_max(0, parent_constr_max_width - padding_east - (*next_start_x));
        }
    }
    else
    {
        next_constraints->_max_width = nt_misc_max(0, parent_constr_max_width - padding_east - padding_west);

        if(*next_start_x == -1)
        {
            *next_start_x = padding_west;
            *next_start_y = padding_north;

            next_constraints->_max_height = nt_misc_max(0, parent_constr_max_height - padding_south - padding_north);
        }
        else
        {
            *next_start_x = padding_west;
            *next_start_y += spacing;

            next_constraints->_max_height = nt_misc_max(0, parent_constr_max_height - padding_south - (*next_start_y));
        }
    }

    return nt_draw_engine_can_object_be_drawn_constr(next_constraints);
}

void _nt_box_layout_manager_arrange_func(struct NTLayoutManager* box_layout_manager, struct NTConstraints* constraints)
{
    assert(box_layout_manager != NULL);
    assert(constraints != NULL);

    struct NTBoxLayoutManager* _box_layout_manager = (struct NTBoxLayoutManager*)box_layout_manager;
    struct Vector* children = _box_layout_manager->_children;

    size_t total_padding_width = _box_layout_manager->_padding.east + _box_layout_manager->_padding.west;
    size_t total_padding_height = _box_layout_manager->_padding.north + _box_layout_manager->_padding.south;

    size_t children_width = 0;
    size_t children_height = 0;
    size_t drawings = 0;

    ssize_t next_start_x = -1, next_start_y = -1;

    struct NTConstraints next_constraints;

    struct NTObject* curr_child;
    int i;
    for(i = 0; i < nt_vec_api_vec_get_count(children); i++) // draw all possible children
    {
        curr_child = *(struct NTObject**)nt_vec_api_vec_at(children, i);
        assert(curr_child != NULL);
        if(!(_get_next(_box_layout_manager, &next_start_x, &next_start_y, &next_constraints, constraints))) 
        {
            nt_log_log("GET_NEXT: %d %d %d %d\n", next_start_x, next_start_y, next_constraints._max_width, next_constraints._max_height);
            break;
        }

        nt_log_log("GET_NEXT: %d %d %d %d\n", next_start_x, next_start_y, next_constraints._max_width, next_constraints._max_height);

        nt_object_draw(curr_child, &next_constraints);

        nt_log_log("nxc----------------- %ld %ld %ld %ld %ld %ld\n", next_constraints._min_width, next_constraints._min_height,
                next_constraints._max_width, next_constraints._max_height, next_constraints.used_x, next_constraints.used_y);

        if(nt_draw_engine_has_object_been_drawn_constr(&next_constraints))
        {
            drawings++;
            _nt_object_set_object_position_based_on_dimensions(curr_child, next_start_x, next_start_y, next_constraints.used_x, next_constraints.used_y);
            if(_box_layout_manager->_orientation == NT_BOX_LAYOUT_MANAGER_ORIENTATION_HORIZONTAL)
            {
                children_height = nt_misc_max(children_height, next_constraints.used_y);
                children_width += next_constraints.used_x;
            }
            else
            {
                children_width = nt_misc_max(children_width, next_constraints.used_x);
                children_height += next_constraints.used_y;
            }
            next_start_x += next_constraints.used_x;
            next_start_y += next_constraints.used_y;
        }
        else
        {
            _nt_object_set_object_position_based_on_dimensions(curr_child, 0, 0, 0, 0);
        }
    }

    nt_constraints_init(&next_constraints, 0, 0, 0, 0);
    for(; i < nt_vec_api_vec_get_count(children); i++) // mark undrawn children as undrawn
    {
        curr_child = *(struct NTObject**)nt_vec_api_vec_at(children, i);
        assert(curr_child != NULL);

        nt_object_draw(curr_child, &next_constraints);
        _nt_object_set_object_position_based_on_dimensions(curr_child, 0, 0, 0, 0);
    }

    if(drawings) // remove one spacing calc if no drawings
    {
        if(_box_layout_manager->_orientation == NT_BOX_LAYOUT_MANAGER_ORIENTATION_HORIZONTAL)
            children_width += _box_layout_manager->_spacing * (drawings - 1);
        else
            children_height += _box_layout_manager->_spacing * (drawings - 1);
    }

    size_t extra_padding_width = ((children_width + total_padding_width) < constraints->_min_width) ?
        constraints->_min_width - children_width - total_padding_width : 0;
    size_t extra_padding_height = ((children_height + total_padding_height) < constraints->_min_height) ?
        constraints->_min_height - children_height - total_padding_height : 0;;

    size_t total_width = total_padding_width + extra_padding_width + children_width;
    size_t total_height = total_padding_height + extra_padding_height + children_height;

    // assert(total_width <= constraints->_max_width);
    // assert(total_height <= constraints->_max_height);

    constraints->used_x = nt_misc_min(total_width, constraints->_max_width);
    constraints->used_y = nt_misc_min(total_height, constraints->_max_height);
}

void _nt_box_layout_manager_get_children_func(const struct NTLayoutManager* box_layout_manager, struct Vector* vec_buff)
{
    assert(box_layout_manager != NULL);
    assert(vec_buff != NULL);

    assert(nt_vec_api_vec_get_count(vec_buff) == 0);

    struct NTBoxLayoutManager* _box_layout_manager = (struct NTBoxLayoutManager*)box_layout_manager;
    size_t child_count = nt_vec_api_vec_get_count(_box_layout_manager->_children);
    int i;
    for(i = 0; i < child_count; i++) assert(nt_vec_api_vec_append(vec_buff, nt_vec_api_vec_at(vec_buff, i)) == 0);
}
