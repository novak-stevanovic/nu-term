#include <stdlib.h>
#include <assert.h>

#include "nt_derived/nt_layout_managers/nt_box_layout_manager.h"
#include "api/nt_vec_api.h"
#include "nt_base/nt_constraints.h"
#include "nt_base/nt_object.h"

void nt_box_layout_manager_init(struct NTBoxLayoutManager* box_layout_manager, NTBoxLayoutManagerOrientation orientation)
{
    assert(box_layout_manager != NULL);

    nt_layout_manager_init((struct NTLayoutManager*)box_layout_manager,
            _nt_box_layout_manager_arrange_func,
            _nt_box_layout_manager_get_children_func);

    box_layout_manager->_orientation = orientation;
    box_layout_manager->_padding = 0;
    box_layout_manager->_spacing = 0;
}

void nt_box_layout_manager_set_padding(struct NTBoxLayoutManager* box_layout_manager, size_t padding)
{
    assert(box_layout_manager != NULL);

    box_layout_manager->_padding = padding;

    //TODO -- redraw?

}
size_t nt_box_layout_manager_get_padding(struct NTBoxLayoutManager* box_layout_manager)
{
    assert(box_layout_manager != NULL);

    return box_layout_manager->_padding;
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

int _get_next(ssize_t* next_start_x, ssize_t* next_start_y, struct NTConstraints* next_constraints)
{
    assert(next_start_x != NULL);
    assert(next_start_y != NULL);
    assert(next_constraints != NULL);
}

void _nt_box_layout_manager_arrange_func(struct NTLayoutManager* box_layout_manager, struct NTConstraints* constraints)
{
    assert(box_layout_manager != NULL);
    assert(constraints != NULL);

    ssize_t next_start_x = -1, next_start_y = -1;
    
    struct NTConstraints next_constraints;

    while(_get_next(&next_start_x, &next_start_y, &next_constraints))
    {
    }
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
