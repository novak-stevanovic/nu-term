#ifndef NT_BOX_CONTAINER_H
#define NT_BOX_CONTAINER_H

#include "nt_base/nt_padding_container.h"

typedef struct NTBox
{
    NTPaddingContainer _base;

} NTBox;

void nt_box_init(NTBox* box);

void nt_box_append_child(NTBox* box, NTObject* object);

const struct NTPadding nt_box_get_padding(const NTBox* box);
void nt_box_set_padding(NTBox* box, const struct NTPadding* new_padding);

#endif // NT_BOX_CONTAINER_H
