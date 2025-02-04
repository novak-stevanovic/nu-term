#include <assert.h>

#include "api/nt_vec_api.h"
#include "nt_base/nt_constraints.h"
#include "nt_base/nt_object.h"
#include "nt_core/nt_draw_engine.h"
#include "nt_derived/nt_layout_managers/nt_simple_layout_manager.h"

void nt_simple_layout_manager_init(struct NTSimpleLayoutManager* simple_layout_manager, struct NTLayoutContainer* layout_container)
{
    assert(simple_layout_manager != NULL);
    assert(layout_container != NULL);

    nt_layout_manager_init((struct NTLayoutManager*)simple_layout_manager,
            layout_container,
            _nt_simple_layout_manager_arrange_func,
            _nt_simple_layout_manager_get_children_func);

    nt_padding_object_init(&simple_layout_manager->_padding_object);
}

void _nt_simple_layout_manager_arrange_func(struct NTLayoutManager* simple_layout_manager, struct NTConstraints* constraints)
{
    // TODO - finish, think about pref size, also think about edge cases like min_height > max_height
    assert(simple_layout_manager != NULL);
    assert(constraints != NULL);

    struct NTLayoutContainer* layout_container = nt_layout_manager_get_layout_container(simple_layout_manager);
    struct NTSimpleLayoutManager* _simple_layout_manager = (struct NTSimpleLayoutManager*)simple_layout_manager;
    struct NTPaddingObject* padding_obj = &_simple_layout_manager->_padding_object;
    assert(layout_container != NULL);
    struct NTObject* _layout_container = (struct NTObject*)layout_container;

    size_t child_start_x, child_start_y;

    child_start_x = padding_obj->west;
    child_start_y = padding_obj->north;

    size_t total_padding_width = padding_obj->east + padding_obj->west;
    size_t total_padding_height = padding_obj->north + padding_obj->south;

    size_t child_min_width = ((constraints->_min_size_x >= total_padding_width) ? constraints->_min_size_x - total_padding_width : 0);
    size_t child_min_height = ((constraints->_min_size_y >= total_padding_height) ? constraints->_min_size_y - total_padding_height : 0);

    size_t child_max_width = ((constraints->_max_size_x >= total_padding_width) ? constraints->_max_size_x - total_padding_width : 0);
    size_t child_max_height = ((constraints->_max_size_y >= total_padding_height) ? constraints->_max_size_y - total_padding_height : 0);

    int child_drawable = nt_draw_engine_can_object_be_drawn(child_min_width, child_max_height, child_max_width, child_max_height);
    if(child_drawable)
    {
        struct NTConstraints child_constraints;
        nt_constraints_init(&child_constraints, child_start_x, child_start_y, child_min_width, child_min_height, child_max_width, child_max_height);

        nt_object_draw(_simple_layout_manager->_container_child, &child_constraints);
        
        _nt_object_set_object_position(_simple_layout_manager->_container_child, &child_constraints);
        // printf("E: %ld %ld\n", _simple_layout_manager->_container_child->_rel_end_x, _simple_layout_manager->_container_child->_rel_end_y);

        constraints->used_x = child_constraints.used_x + padding_obj->east + padding_obj->west;
        constraints->used_y = child_constraints.used_y + padding_obj->north + padding_obj->south;
    }
    else
    {
        constraints->used_x = 0;
        constraints->used_y = 0;
    }
    // printf("C: %ld %ld %ld %ld S: %ld %ld\n", child_min_width, child_min_height, child_max_width, child_max_height, child_start_x, child_start_y);
    // printf("U: %ld %ld\n", constraints->used_x, constraints->used_y);
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

//TODO -- redraw?
void nt_simple_layout_manager_set_container_child(struct NTSimpleLayoutManager* simple_layout_manager, struct NTObject* object)
{
    assert(simple_layout_manager != NULL);

    simple_layout_manager->_container_child = object;
    // TODO -- set child?
    object->_parent = (struct NTContainer*)nt_layout_manager_get_layout_container((struct NTLayoutManager*)simple_layout_manager);
}
