#ifndef NT_PADDING_OBJECT_H
#define NT_PADDING_OBJECT_H

#include <stddef.h>

struct NTPaddingObject
{
    size_t north, east, south, west;
};

void nt_padding_object_init(struct NTPaddingObject* padding_object);

size_t nt_padding_object_get_height(struct NTPaddingObject* padding_object);
size_t nt_padding_object_get_width(struct NTPaddingObject* padding_object);

void nt_padding_object_conform_height_to_size(struct NTPaddingObject* padding_object, size_t height);
void nt_padding_object_conform_width_to_size(struct NTPaddingObject* padding_object, size_t width);

void nt_padding_object_conform_to_size(struct NTPaddingObject* padding_object, size_t width, size_t height);

#endif
