// INTERNAL HEADER FILE - DO NOT INCLUDE DIRECTLY.

#ifndef __GDS_HASH_MAP_DEF_H__
#define __GDS_HASH_MAP_DEF_H__

#include <string.h>
#ifndef __GDS_HASH_MAP_DEF_ALLOW__
#error "Do not include directly."
#endif // __GDS_HASH_MAP_DEF_ALLOW__

#include <stdbool.h>

#define __GDS_VECTOR_DEF_ALLOW__
#include "gds_vector_def.h"

struct GDSHashMap
{
    struct GDSVector _data;

    size_t _key_data_size, _value_data_size;
    size_t (*_hash_func)(const void* key, size_t max_value);
    bool (*_key_compare_func)(const void* key1, const void* key2);

    double _max_load_factor;
    size_t _entry_count;
};

#endif // __GDS_HASH_MAP_DEF_H__
