#include <assert.h>

#include "nt_shared/nt_padding_object.h"
#include "nt_misc.h"

void nt_padding_object_init(struct NTPaddingObject* padding_object)
{
    assert(padding_object != NULL);

    padding_object->north = 0;
    padding_object->east = 0;
    padding_object->south = 0;
    padding_object->west = 0;


}

size_t nt_padding_object_get_height(struct NTPaddingObject* padding_object)
{
    assert(padding_object != NULL);

    return padding_object->south + padding_object->north;
}

size_t nt_padding_object_get_width(struct NTPaddingObject* padding_object)
{
    assert(padding_object != NULL);

    return padding_object->east + padding_object->west;
}

void nt_padding_object_conform_height_to_size(struct NTPaddingObject* padding_object, size_t height)
{
    assert(padding_object != NULL);

    size_t curr_height = padding_object->south + padding_object->north;

    if(curr_height > height)
    {
        size_t extra_height = curr_height - height;

        size_t subtraction = nt_misc_min((ssize_t)padding_object->south, (ssize_t)extra_height);

        padding_object->south -= subtraction;
        extra_height -= subtraction;

        padding_object->north -= extra_height;
    }
    else if(curr_height < height)
    {
        padding_object->south += (height - curr_height);
    }
    else return;
}
void nt_padding_object_conform_width_to_size(struct NTPaddingObject* padding_object, size_t width)
{
    assert(padding_object != NULL);

    size_t curr_width = padding_object->west + padding_object->east;

    if(curr_width > width)
    {
        size_t extra_width = curr_width - width;

        size_t subtraction = nt_misc_min((ssize_t)padding_object->east, (ssize_t)extra_width);

        padding_object->east -= subtraction;
        extra_width -= subtraction;

        padding_object->west -= extra_width;
    }
    else if(curr_width < width)
    {
        padding_object->east += (width - curr_width);
    }
    else return;
}

void nt_padding_object_conform_to_size(struct NTPaddingObject* padding_object, size_t width, size_t height)
{
    assert(padding_object != NULL);

    nt_padding_object_conform_height_to_size(padding_object, height);
    nt_padding_object_conform_width_to_size(padding_object, width);
}
