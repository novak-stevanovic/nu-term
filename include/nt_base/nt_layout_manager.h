#ifndef NT_LAYOUT_MANAGER_H
#define NT_LAYOUT_MANAGER_H

struct NTLayoutContainer;
struct NTConstraints;
struct Vector;

struct NTLayoutManager
{
    struct NTLayoutContainer* _layout_container;

    void (*_arrange_func)(struct NTLayoutManager*, struct NTConstraints*);
    void (*_get_children_func)(const struct NTLayoutManager*, struct Vector*);
};

void nt_layout_manager_init(struct NTLayoutManager* layout_manager,
        struct NTLayoutContainer* layout_container,
        void (*arrange_func)(struct NTLayoutManager*, struct NTConstraints*),
        void (*get_children_func)(const struct NTLayoutManager*, struct Vector*));

void nt_layout_manager_arrange(struct NTLayoutManager* layout_manager, struct NTConstraints* constraints);
void nt_layout_manager_get_children(const struct NTLayoutManager* layout_manager, struct Vector* vec_buff);

struct NTLayoutContainer* nt_layout_manager_get_layout_container(struct NTLayoutManager* layout_manager);

#endif
