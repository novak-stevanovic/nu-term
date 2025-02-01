#ifndef NT_CONTAINER_H
#define NT_CONTAINER_H

#include "nt_base/nt_object.h"

struct NTObject;
struct NTObjectSizeConstraints;
struct Vector;

struct NTContainer
{
    struct NTObject _base;
    struct NTSolidColorBlock* _background; //TODO
};

void nt_container_init(struct NTContainer* container,
        void (*arrange_content_func)(struct NTObject*, struct NTObjectSizeConstraints*),
        void (*get_children_func)(const struct NTObject*, struct Vector* vec_buff));

#define NT_CONTAINER_NO_BACKGROUND -1
void nt_container_set_background(struct NTContainer* container, ssize_t color_code);

#endif
