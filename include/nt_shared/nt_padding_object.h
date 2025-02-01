#ifndef NT_PADDING_OBJECT_H
#define NT_PADDING_OBJECT_H

#include <stddef.h>

struct NTPaddingObject
{
    size_t north, east, south, west;
};

void nt_padding_object_init(struct NTPaddingObject* padding_object);

#endif
