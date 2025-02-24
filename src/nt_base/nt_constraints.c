#include <stdio.h>

#include "nt_base/nt_constraints.h"
#include "nt_base/nt_object.h"
#include "nt_misc.h"

void nt_constraints_init(struct NTConstraints* constraints,
        size_t min_width, size_t min_height,
        size_t max_width, size_t max_height)
{
    if(((min_width == 0) && (max_width == 0)) || ((min_height == 0) && (max_height == 0)))
    {
        constraints->_min_width = 0;
        constraints->_max_width = 0;
        constraints->_min_height = 0;
        constraints->_max_height = 0;
    }
    else
    {
        constraints->_min_width = min_width;
        constraints->_min_height = min_height;
        constraints->_max_width = max_width;
        constraints->_max_height = max_height;

        // printf("CON: %d %d %d %d\n", min_width, min_height, max_width, max_height);
    }
}

size_t nt_constraints_determine_min_size(size_t constraint_min_size, size_t obj_min_size, size_t constraint_max_size)
{
    return ((obj_min_size >= constraint_min_size) && (obj_min_size <= constraint_max_size)) ? obj_min_size : constraint_min_size;
}

size_t nt_constraints_determine_max_size(size_t constraint_max_size, size_t obj_max_size, size_t constraint_min_size)
{
    return ((obj_max_size <= constraint_max_size) && (obj_max_size >= constraint_min_size)) ? obj_max_size : constraint_max_size;
}

void nt_constraints_apply_object_restrictions(struct NTConstraints* constraints, struct NTObject* object)
{
    size_t min_width = nt_constraints_determine_min_size(constraints->_min_width, object->_min_width, constraints->_min_width);
    size_t min_height = nt_constraints_determine_min_size(constraints->_min_height, object->_min_height, constraints->_min_height);

    size_t max_width = nt_constraints_determine_max_size(constraints->_max_width, object->_max_width, constraints->_min_width);
    size_t max_height = nt_constraints_determine_max_size(constraints->_max_height, object->_max_height, constraints->_min_height);

    if(object->_pref_width != NT_OBJECT_PREF_SIZE_UNSPECIFIED)
    {
        size_t width = nt_misc_conform_val(min_width, object->_pref_width, max_width);

        constraints->_min_width = width;
    }
    else
    {
        constraints->_min_width = min_width;
        constraints->_max_width = max_width;
    }

    if(object->_pref_height != NT_OBJECT_PREF_SIZE_UNSPECIFIED)
    {
        size_t height = nt_misc_conform_val(min_height, object->_pref_height, max_height);

        constraints->_min_height = height;
    }
    else
    {
        constraints->_min_height = min_height;
        constraints->_max_height = max_height;
    }

}
