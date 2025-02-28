#include "nt_base/nt_container.h"
#include "nt_base/nt_container_child_data.h"

#include "gds_array.h"
#include "nt_base/nt_window.h"

// NTObject's _object_arrange_func override
static void _object_arrange_func(NTObject* object);

// NTObject's _object_display_func override
static void _object_display_func(NTObject* object);

// Part of _object_arrange_func(NTObject*) - it updates the coordinates of the background and marks
// it for redrawing if needed.
static void _arrange_background(NTContainer* container);

// Part of _object_arrange_func(NTObject*) - it updates the coordinates of each child
// and marks them for redrawing if needed. 
static void _arrange_children(NTContainer* container, GDSArray* children_data);

// ------------------------------------------------------------------------------------------------------------

void nt_container_init(NTContainer* container, 

        void (*object_calculate_req_size_func)(const NTObject* object,
            size_t* out_width, size_t* out_height),

        void (*container_arrange_func)(const NTContainer* container, 
            struct GDSArray* out_children_data))
{
    nt_object_init((NTObject*)container, 
            object_calculate_req_size_func,
            _object_arrange_func,
            _object_display_func);

    container->_background = NULL;
    container->_container_arrange_func = container_arrange_func;
}
            
const GDSVector* nt_container_get_children(const NTContainer* container)
{
    return &container->_children;
}

NTWindow* nt_container_get_background(NTContainer* container)
{
    return container->_background;
}

void nt_container_set_background(NTContainer* container, NTWindow* new_background)
{
    container->_background = new_background;
    ((NTObject*)container->_background)->_parent = container;
    // TODO redraw
}

void nt_container_position_child(NTObject* child, const NTBounds* new_bounds)
{
    const NTBounds* old_bounds = &child->_bounds;

    nt_object_set_position(child, new_bounds);

    // if the size changes, the content inside the object needs to rearrange
    if(!nt_bounds_are_equal_size(old_bounds, new_bounds))
    {
        nt_object_arrange(child);
    }
}

// ------------------------------------------------------------------------------------------------------------

static void _arrange_background(NTContainer* container)
{
    NTObject* _object = (NTObject*)container;
    NTObject* _background = (NTObject*)container->_background;

    NTBounds background_bounds;
    nt_bounds_init(&background_bounds, 0, 0,
            nt_bounds_calculate_width(&_object->_bounds),
            nt_bounds_calculate_height(&_object->_bounds));

    nt_container_position_child(_background, &background_bounds);
}

static void _object_arrange_func(NTObject* object)
{
    NTContainer* _object = (NTContainer*)object;

    _arrange_background(_object);

    GDSArray children_data;
    size_t child_count = gds_vector_get_count(&_object->_children);

    gds_array_init(&children_data, child_count, sizeof(NTContainerChildData));

    _object->_container_arrange_func(_object, &children_data);

    _arrange_children(_object, &children_data);

}

static void _object_display_func(NTObject* object)
{
    NTContainer* _object = (NTContainer*)object;
    NTObject* _background = (NTObject*)_object->_background;

    if(_background->_tainted) nt_object_display(_background);

    GDSVector* children = &_object->_children;
    size_t child_count = gds_vector_get_count(children);

    size_t i = 0;
    NTObject* curr_child;
    for(i = 0; i < child_count; i++)
    {
        curr_child = *(NTObject**)gds_vector_at(children, i);
        if(curr_child->_tainted) nt_object_display(curr_child);
    }
}

static void _arrange_children(NTContainer* container, GDSArray* children_data)
{
    size_t child_count = gds_array_get_count(children_data);
    NTObject* _background = (NTObject*)container->_background;

    NTContainerChildData* child_data;
    NTObject* child;
    size_t i;
    for(i = 0; i < child_count; i++)
    {
        child_data = gds_array_at(children_data, i);

        child = child_data->child;

        nt_container_position_child(child, &child_data->bounds);

        if(child->_tainted) _background->_tainted = true;
    }
}
