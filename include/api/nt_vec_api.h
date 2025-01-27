#ifndef NT_VEC_API_H
#define NT_VEC_API_H

#include <stddef.h>
#include <stdio.h>

struct Vector {};
// typedef struct Vector GDSVector;

struct Vector* nt_vec_api_vec_create(size_t min_count, size_t resize_count, size_t element_size, void (*on_removal_func)(void*));
void nt_vec_api_vec_destuct(struct Vector* vector);

void* nt_vec_api_vec_at(struct Vector* vec, size_t pos);

int nt_vec_api_vec_append(struct Vector* vector, void* data);

ssize_t nt_vec_api_vec_get_count(struct Vector* vector);

int nt_vec_api_vec_set_size_gen(struct Vector* vector, size_t new_size, void* (*el_gen_func)(void*), void* data);

#endif
