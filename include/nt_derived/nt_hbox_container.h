#ifndef NT_HBOX_CONTAINER_H
#define NT_HBOX_CONTAINER_H

#include "nt_derived/nt_box_container.h"

struct NTHBoxContainer
{
    struct NTBoxContainer _base;
};

void nt_hbox_container_init(struct NTHBoxContainer* hbox_container);

#endif
