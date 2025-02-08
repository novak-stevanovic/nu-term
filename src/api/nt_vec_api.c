#include <assert.h>

#include "api/nt_vec_api.h"

NTVector* nt_vector_create(size_t min_count, size_t resize_count, size_t element_size, void (*on_removal_func)(void*))
{
    return gds_vec_create(min_count, resize_count, element_size, on_removal_func);
}

void nt_vector_destruct(NTVector* vector)
{
    gds_vec_destruct(vector);
}

void* nt_vector_at(NTVector* vec, size_t pos)
{
    return gds_vec_at(vec, pos);
}

int nt_vector_append(NTVector* vector, void* data)
{
    return gds_vec_append(vector, data);
}

ssize_t nt_vector_get_count(NTVector* vector)
{
    return gds_vec_get_count(vector);
}

int nt_vector_set_size(NTVector* vector, size_t new_size, void (*assign_func)(void*, void*), void* data)
{
    int set_size_status = gds_vec_set_size(vector, new_size, assign_func, data);
    assert(set_size_status == 0);

    return set_size_status;
}

size_t nt_vec_api_get_struct_size()
{
    return gds_vec_get_struct_size();

}
