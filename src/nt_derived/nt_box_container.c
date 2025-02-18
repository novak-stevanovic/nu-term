#include <assert.h>

#include "nt_derived/nt_box_container.h"
#include "nt_base/nt_constraints.h"
#include "nt_misc.h"

void nt_box_container_init(struct NTBoxContainer* box_container,

        void* (*draw_content_init_func)(struct NTContainer* box_container, struct NTConstraints* constraints),

        struct NTObject* (*get_next_func)(struct NTContainer* box_container, struct NTConstraints* constraints,
            struct NTConstraints* child_constraints, void* data),

        void (*post_draw_child_func)(struct NTContainer* box_container, struct NTObject* child,
            struct NTConstraints* parent_constraints, struct NTConstraints* child_constraints,
            void* data),

        void (*conclude_draw_func)(struct NTContainer* box_container, struct NTConstraints* parent_constraints, void* data))
{
    nt_container_init((struct NTContainer*)box_container,
            draw_content_init_func,
            get_next_func,
            post_draw_child_func,
            conclude_draw_func);

    nt_padding_object_init(&box_container->_padding);
    box_container->_spacing = 0;
}

void nt_box_container_add_child(struct NTBoxContainer* box_container, struct NTObject* child)
{
    assert(box_container != NULL);
    assert(child != NULL);

    struct NTContainer* _box_container = (struct NTContainer*)box_container;

    gds_vector_push_back(&_box_container->_children, &child);

}

size_t nt_box_container_calculate_total_spacing(size_t spacing, size_t drawn_children)
{
    return (drawn_children > 0) ? (drawn_children - 1) * spacing : 0;
}

// ----------------------------------------------------------------------------------------------------------------------------------
