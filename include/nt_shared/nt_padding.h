#ifndef NT_PADDING_OBJECT_H
#define NT_PADDING_OBJECT_H

#include <stddef.h>

struct NTPadding
{
    size_t north, east, south, west;
};

void nt_padding_init_default(struct NTPadding* padding_object);

void nt_padding_init(struct NTPadding* padding,
        size_t north, size_t east, size_t south, size_t west);

void nt_padding_init_copy(struct NTPadding* dest, const struct NTPadding* src);

size_t nt_padding_calculate_width(const struct NTPadding* padding_object);
size_t nt_padding_calculate_height(const struct NTPadding* padding_object);

// void nt_padding_conform_height_to_size(struct NTPadding* padding_object, size_t height);
// void nt_padding_conform_width_to_size(struct NTPadding* padding_object, size_t width);
//
// void nt_padding_conform_to_size(struct NTPadding* padding_object, size_t width, size_t height);

#endif
