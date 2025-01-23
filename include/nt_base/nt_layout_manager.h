#ifndef NT_LAYOUT_MANAGER_H
#define NT_LAYOUT_MANAGER_H

struct NTLayoutContainer;
struct NTObjectSizeConstraints;
struct Vector;

struct NTLayoutManager
{
    struct NTLayoutContainer* _layout_container;

    void (*_arrange_func)(struct NTLayoutManager*, struct NTObjectSizeConstraints*);
    void (*_get_children_func)(const struct NTLayoutManager*, struct Vector* vec_buff);
};

void nt_layout_manager_init(struct NTLayoutManager* layout_manager,
        struct NTLayoutContainer* layout_container,
        void (*arrange_func)(struct NTLayoutManager*, struct NTObjectSizeConstraints*),
        void (*get_children_func)(const struct NTLayoutManager*, struct Vector*));

void nt_layout_manager_arrange(struct NTLayoutManager* layout_manager, struct NTObjectSizeConstraints* constraints);
void nt_layout_manager_get_children(const struct NTLayoutManager* layout_manager, struct Vector* vec_buff);

#endif
