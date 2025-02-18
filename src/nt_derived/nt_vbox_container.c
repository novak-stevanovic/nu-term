#include <assert.h>

#include "nt_derived/nt_vbox_container.h"

// ----------------------------------------------------------------------------------------------------------------------------------

static void* _nt_vbox_container_draw_content_init_func(struct NTContainer* vbox_container, struct NTConstraints* constraints);

static struct NTObject* _nt_vbox_container_get_next_func(struct NTContainer* vbox_container, struct NTConstraints* constraints,
    struct NTConstraints* child_constraints, void* data);

static void _nt_vbox_container_post_draw_child_func(struct NTContainer* vbox_container, struct NTObject* child,
    struct NTConstraints* parent_constraints, struct NTConstraints* child_constraints, void* data);

static void _nt_vbox_container_conclude_draw_func(struct NTContainer* vbox_container, struct NTConstraints* parent_constraints, void* data);

// ----------------------------------------------------------------------------------------------------------------------------------

void nt_vbox_container_init(struct NTVBoxContainer* vbox_container)
{
    assert(vbox_container != NULL);

    nt_box_container_init((struct NTBoxContainer*)vbox_container,
            _nt_vbox_container_draw_content_init_func,
            _nt_vbox_container_get_next_func,
            _nt_vbox_container_post_draw_child_func,
            _nt_vbox_container_conclude_draw_func);
}

static void* _nt_vbox_container_draw_content_init_func(struct NTContainer* vbox_container, struct NTConstraints* constraints)
{
}

static struct NTObject* _nt_vbox_container_get_next_func(struct NTContainer* vbox_container, struct NTConstraints* constraints,
    struct NTConstraints* child_constraints, void* data)
{
}

static void _nt_vbox_container_post_draw_child_func(struct NTContainer* vbox_container, struct NTObject* child,
    struct NTConstraints* parent_constraints, struct NTConstraints* child_constraints, void* data)
{
}

static void _nt_vbox_container_conclude_draw_func(struct NTContainer* vbox_container, struct NTConstraints* parent_constraints, void* data)
{
}
