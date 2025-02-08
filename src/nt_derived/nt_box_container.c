#include <assert.h>

#include "nt_derived/nt_box_container.h"

// ----------------------------------------------------------------------------------------------------------------------------------

struct NTContainerDataObject;

static void* _nt_box_container_draw_content_init_func(struct NTContainer* container, struct NTConstraints* constraints);

static struct NTObject* _nt_box_container_get_next_func(struct NTContainer* container, struct NTConstraints* constraints,
    struct NTConstraints* child_constraints, void* data);

static void _nt_box_container_post_draw_child_func(struct NTContainer* container, struct NTObject* child,
    struct NTConstraints* parent_constraints, struct NTConstraints* child_constraints, void* data);

static void _nt_box_container_conclude_draw_func(struct NTContainer* container, struct NTConstraints* parent_constraints, void* data);

// ----------------------------------------------------------------------------------------------------------------------------------

void nt_box_container_init(struct NTBoxContainer* box_container, NTBoxContainerOrientation orientation)
{
    assert(box_container != NULL);

    nt_container_init((struct NTContainer*)box_container,
            _nt_box_container_draw_content_init_func,
            _nt_box_container_get_next_func,
            _nt_box_container_post_draw_child_func,
            _nt_box_container_conclude_draw_func);

    box_container->_orientation = orientation;
}

// ----------------------------------------------------------------------------------------------------------------------------------

struct NTContainerDataObject
{
    size_t drawing_count;
    ssize_t last_start_x, last_start_y, last_end_x, last_end_y;
};

static void* _nt_box_container_draw_content_init_func(struct NTContainer* container, struct NTConstraints* constraints)
{

    struct NTContainerDataObject* data_obj = (struct NTContainerDataObject*)malloc(sizeof(struct NTContainerDataObject));

    data_obj->drawing_count = 0;
    data_obj->last_start_x = -1;
    data_obj->last_start_y = -1;
    data_obj->last_end_x = -1;
    data_obj->last_end_y = -1;

    return data_obj;
}

static struct NTObject* _nt_box_container_get_next_func(struct NTContainer* container, struct NTConstraints* constraints,
    struct NTConstraints* child_constraints, void* data)
{
    return NULL;
}

static void _nt_box_container_post_draw_child_func(struct NTContainer* container, struct NTObject* child,
    struct NTConstraints* parent_constraints, struct NTConstraints* child_constraints, void* data)
{
}

static void _nt_box_container_conclude_draw_func(struct NTContainer* container, struct NTConstraints* parent_constraints, void* data)
{
    free(data);
}
