#include "api/nt_vec_api.h"
#include "lib/gds_vector.h"

struct Vector* nt_vec_api_vec_create(size_t min_count, size_t resize_count, size_t element_size)
{
    return (struct Vector*)gds_vec_create(min_count, resize_count, element_size);
}

int nt_vec_api_vec_append(struct Vector* vector, void* data)
{
    return gds_vec_append((struct GDSVector*)vector, data);
}

ssize_t nt_vec_api_vec_get_count(struct Vector* vector)
{
    return gds_vec_get_count((struct GDSVector*)vector);
}
