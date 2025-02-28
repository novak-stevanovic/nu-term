#include "nt_shared/nt_padding.h"

void nt_padding_init_default(struct NTPadding* padding_object)
{
    padding_object->north = 0;
    padding_object->east = 0;
    padding_object->south = 0;
    padding_object->west = 0;
}

void nt_padding_init(struct NTPadding* padding,
        size_t north, size_t east, size_t south, size_t west)
{
    padding->north = north;
    padding->east = east;
    padding->south = south;
    padding->west = west;
}

void nt_padding_init_copy(struct NTPadding* dest, const struct NTPadding* src)
{
    nt_padding_init(dest, src->north, src->east, src->south, src->west);
}

size_t nt_padding_calculate_width(const struct NTPadding* padding_object)
{
    return padding_object->east + padding_object->west;
}

size_t nt_padding_calculate_height(const struct NTPadding* padding_object)
{
    return padding_object->north + padding_object->south;
}

