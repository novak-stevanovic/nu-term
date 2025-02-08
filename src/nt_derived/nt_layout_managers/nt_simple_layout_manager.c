#include <assert.h>

#include "nt_derived/nt_layout_managers/nt_simple_layout_manager.h"
#include "api/nt_vec_api.h"
#include "nt_base/nt_constraints.h"
#include "nt_base/nt_object.h"
#include "nt_core/nt_draw_engine.h"
#include "nt_log.h"

void nt_simple_layout_manager_init(struct NTSimpleLayoutManager* simple_layout_manager)
{
    assert(simple_layout_manager != NULL);

    nt_layout_manager_init((struct NTLayoutManager*)simple_layout_manager,
            _nt_simple_layout_manager_arrange_func,
            _nt_simple_layout_manager_get_children_func);

    nt_padding_object_init(&simple_layout_manager->_padding_object);

    simple_layout_manager->_child = NULL;
}

void _nt_simple_layout_manager_arrange_func(struct NTLayoutManager* simple_layout_manager, struct NTConstraints* constraints)
{
    // TODO - finish
    assert(simple_layout_manager != NULL);
    assert(constraints != NULL);

    struct NTLayoutContainer* layout_container = nt_layout_manager_get_layout_container(simple_layout_manager);
    assert(layout_container != NULL);
    struct NTSimpleLayoutManager* _simple_layout_manager = (struct NTSimpleLayoutManager*)simple_layout_manager;
    struct NTPaddingObject* padding_obj = &_simple_layout_manager->_padding_object;

    if(_simple_layout_manager->_child == NULL)
    {
        constraints->used_x = constraints->_min_width;
        constraints->used_y = constraints->_min_height;
        _nt_object_set_object_position_based_on_dimensions(_simple_layout_manager->_child, 0, 0, 0, 0);
        return;
    }

    size_t child_start_x, child_start_y;

    size_t total_padding_width = padding_obj->east + padding_obj->west;
    size_t total_padding_height = padding_obj->north + padding_obj->south;

    child_start_x = padding_obj->west;
    child_start_y = padding_obj->north;

    size_t child_min_width = 0;
    size_t child_min_height = 0;

    size_t child_max_width = ((constraints->_max_width >= total_padding_width) ? constraints->_max_width - total_padding_width : 0);
    size_t child_max_height = ((constraints->_max_height >= total_padding_height) ? constraints->_max_height - total_padding_height : 0);

    struct NTConstraints child_constraints;
    nt_constraints_init(&child_constraints, child_min_width, child_min_height, child_max_width, child_max_height);
    nt_log_log("CONSTRAINTS: %ld %ld %ld %ld", child_min_width, child_min_height, child_max_width, child_max_height);

    if(_simple_layout_manager->_child) nt_object_draw(_simple_layout_manager->_child, &child_constraints);

    size_t child_used_x, child_used_y;
    child_used_x = child_constraints.used_x;
    child_used_y = child_constraints.used_y;

    nt_log_log("CH_USED: %ld %ld\n", child_used_x, child_used_y);

    nt_log_log("%ld + %ld < %ld?\n", total_padding_width, child_used_x, constraints->_min_width);

    size_t extra_padding_width = ((total_padding_width + child_used_x) < constraints->_min_width) ?
        (constraints->_min_width - total_padding_width - child_used_x) : 0;
    size_t extra_padding_height = ((total_padding_height + child_used_y) < constraints->_min_height) ?
        (constraints->_min_height - total_padding_height - child_used_y) : 0;

    constraints->used_x = child_used_x + total_padding_width + extra_padding_width;
    constraints->used_y = child_used_y + total_padding_height + extra_padding_height;

    if(_simple_layout_manager->_child)
    {
        _nt_object_set_object_position_based_on_dimensions(_simple_layout_manager->_child,
                child_start_x, child_start_y,
                child_start_x + child_used_x, child_start_y + child_used_y);
    }
}

void _nt_simple_layout_manager_get_children_func(const struct NTLayoutManager* simple_layout_manager, struct Vector* vec_buff)
{
    assert(simple_layout_manager != NULL);
    assert(vec_buff != NULL);
    assert(nt_vec_api_vec_get_count(vec_buff) == 0);

    struct NTSimpleLayoutManager* _simple_layout_manager = (struct NTSimpleLayoutManager*)simple_layout_manager;

    assert(nt_vec_api_vec_append(vec_buff, &_simple_layout_manager->_child) == 0);
}

struct NTObject* nt_simple_layout_manager_get_child(const struct NTSimpleLayoutManager* simple_layout_manager)
{
    assert(simple_layout_manager != NULL);

    return simple_layout_manager->_child;
}

//TODO -- redraw?
void nt_simple_layout_manager_set_child(struct NTSimpleLayoutManager* simple_layout_manager, struct NTObject* object)
{
    assert(simple_layout_manager != NULL);

    simple_layout_manager->_child = object;
    // TODO -- set child?
    object->_parent = (struct NTContainer*)nt_layout_manager_get_layout_container((struct NTLayoutManager*)simple_layout_manager);
}
