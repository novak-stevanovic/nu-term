#include <assert.h>

#include "nt_shared/nt_padding_object.h"

void nt_padding_object_init(struct NTPaddingObject* padding_object)
{
    assert(padding_object != NULL);

    padding_object->north = 0;
    padding_object->east = 0;
    padding_object->south = 0;
    padding_object->west = 0;

}
