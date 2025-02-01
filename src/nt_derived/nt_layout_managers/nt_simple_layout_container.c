#include <assert.h>

#include "api/nt_vec_api.h"
#include "nt_base/nt_object.h"
#include "nt_derived/nt_layout_managers/nt_simple_layout_manager.h"

void nt_simple_layout_manager_init(struct NTSimpleLayoutManager* simple_layout_manager, struct NTLayoutContainer* layout_container)
{
    assert(simple_layout_manager != NULL);
    assert(layout_container != NULL);

    nt_padding_object_init(&simple_layout_manager->_padding_object);
}

void _nt_simple_layout_manager_arrange_func(struct NTLayoutManager* simple_layout_manager, struct NTObjectSizeConstraints* constraints)
{
    // TODO - finish, think about pref size, also think about edge cases like min_height > max_height
    assert(simple_layout_manager != NULL);
    assert(constraints != NULL);

    struct NTLayoutContainer* layout_container = nt_layout_manager_get_layout_container(simple_layout_manager);
    struct NTSimpleLayoutManager* _simple_layout_manager = (struct NTSimpleLayoutManager*)simple_layout_manager;
    assert(layout_container != NULL);
    struct NTObject* _layout_container = (struct NTObject*)layout_container;

    size_t child_start_x, child_start_y;

    child_start_x = _simple_layout_manager->_padding_object.east;
    child_start_y = _simple_layout_manager->_padding_object.north;

    size_t child_max_height, child_max_width;

    child_max_height = constraints->_max_size_x - _simple_layout_manager->_padding_object.east - _simple_layout_manager->_padding_object.west;
    child_max_width = constraints->_max_size_y - _simple_layout_manager->_padding_object.north - _simple_layout_manager->_padding_object.south;

    struct NTObjectSizeConstraints child_constraints;
    nt_object_size_constraints_init(&child_constraints, 0, 0, child_max_width, child_max_height);

    nt_object_draw(_layout_container, &child_constraints);

    constraints->used_x = child_constraints.used_x + _simple_layout_manager->_padding_object.east + _simple_layout_manager->_padding_object.west;
    constraints->used_y = child_constraints.used_y + _simple_layout_manager->_padding_object.north + _simple_layout_manager->_padding_object.south;
}

void _nt_simple_layout_manager_get_children_func(const struct NTLayoutManager* simple_layout_manager, struct Vector* vec_buff)
{
    assert(simple_layout_manager != NULL);
    assert(vec_buff != NULL);
    assert(nt_vec_api_vec_get_count(vec_buff) == 0);

    struct NTSimpleLayoutManager* _simple_layout_manager = (struct NTSimpleLayoutManager*)simple_layout_manager;

    assert(nt_vec_api_vec_append(vec_buff, &_simple_layout_manager->_container_child) == 0);
}

struct NTObject* nt_simple_layout_manager_get_container_child(const struct NTSimpleLayoutManager* simple_layout_manager)
{
    assert(simple_layout_manager != NULL);

    return simple_layout_manager->_container_child;
}

//TODO
void nt_simple_layout_manager_set_container_child(const struct NTSimpleLayoutManager* simple_layout_manager, struct NTObject* object)
{
    assert(1 != 1);
}
