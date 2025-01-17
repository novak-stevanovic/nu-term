#ifndef NT_LAYOUT_MANAGER_H
#define NT_LAYOUT_MANAGER_H

struct NTLayoutContainer;

struct NTLayoutManager
{
    struct NTLayoutContainer* _layout_container;

    void (*_arrange_func)(struct NTLayoutManager*, void*);
    struct Vector* (*_get_children_func)(const struct NTLayoutManager*);
};

void nt_layout_manager_init(struct NTLayoutManager* layout_manager,
        struct NTLayoutContainer* layout_container,
        void (*arrange_func)(struct NTLayoutManager*, void*),
        struct Vector* (*get_children_func)(const struct NTLayoutManager*));

void nt_layout_manager_arrange(struct NTLayoutManager* layout_manager);
struct Vector* nt_layout_manager_get_children(const struct NTLayoutManager* layout_manager);

#endif
