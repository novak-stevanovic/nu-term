#include "api/nt_vec_api.h"
#include "lib/gds_vector.h"

struct Vector* nt_vec_api_vec_create(size_t min_count, size_t resize_count, size_t element_size, void (*on_removal_func)(void*))
{
    return (struct Vector*)gds_vec_create(min_count, resize_count, element_size, on_removal_func);
}

void nt_vec_api_vec_destuct(struct Vector* vector)
{
    gds_vec_destruct((struct GDSVector*)vector);
}

void* nt_vec_api_vec_at(struct Vector* vec, size_t pos)
{
    return gds_vec_at((struct GDSVector*)vec, pos);
}

int nt_vec_api_vec_append(struct Vector* vector, void* data)
{
    return gds_vec_append((struct GDSVector*)vector, data);
}

ssize_t nt_vec_api_vec_get_count(struct Vector* vector)
{
    return gds_vec_get_count((struct GDSVector*)vector);
}

int nt_vec_api_vec_set_size_gen(struct Vector* vector, size_t new_size, void* (*el_gen_func)(void*), void* data)
{
    int a = gds_vec_set_size_gen((struct GDSVector*)vector, new_size, el_gen_func, data);

    return a;
}
