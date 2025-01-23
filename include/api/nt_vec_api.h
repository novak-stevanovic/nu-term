#ifndef NT_VEC_API_H
#define NT_VEC_API_H

#include <stddef.h>
#include <stdio.h>

struct Vector {};
// typedef struct Vector GDSVector;

struct Vector* nt_vec_api_vec_create(size_t min_count, size_t resize_count, size_t element_size);

int nt_vec_api_vec_append(struct Vector* vector, void* data);

ssize_t nt_vec_api_vec_get_count(struct Vector* vector);

#endif
