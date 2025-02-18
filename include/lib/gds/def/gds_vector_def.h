// INTERNAL HEADER FILE - DO NOT INCLUDE DIRECTLY.

#ifndef __GDS_VECTOR_DEF_H__
#define __GDS_VECTOR_DEF_H__

#include "gds.h"
#include <stdbool.h>

#ifndef __GDS_VECTOR_DEF_ALLOW__
#error "Do not include directly."
#endif // __GDS_VECTOR_DEF_ALLOW__

// ---------------------------------------------------------------------------------------------------------------------------------------

#define __GDS_ARRAY_DEF_ALLOW__
#include "gds_array_def.h"

struct GDSVector
{
    struct GDSArray _data;
    double _resize_factor;
};

#endif // __GDS_VECTOR_DEF_H__
