#ifndef NT_VBOX_CONTAINER_H
#define NT_VBOX_CONTAINER_H

#include "nt_derived/nt_box_container.h"

struct NTVBoxContainer
{
    struct NTBoxContainer _base;
};

void nt_vbox_container_init(struct NTVBoxContainer* vbox_container);

#endif
