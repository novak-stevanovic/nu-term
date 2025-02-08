#ifndef NT_VEC_API_H
#define NT_VEC_API_H

#include <stddef.h>
#include <stdio.h>

#include "lib/gds_vector.h"

typedef GDSVector NTVector;

NTVector* nt_vector_create(size_t min_count, size_t resize_count, size_t element_size, void (*on_removal_func)(void*));
void nt_vector_destruct(NTVector* vector);

void* nt_vector_at(NTVector* vec, size_t pos);

int nt_vector_append(NTVector* vector, void* data);

ssize_t nt_vector_get_count(NTVector* vector);

int nt_vector_set_size(NTVector* vector, size_t new_size, void (*assign_func)(void*, void*), void* data);

size_t nt_vector_get_struct_size();

#endif
