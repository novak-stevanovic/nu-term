#ifndef _NT_OBJECT_VECTOR_H_
#define _NT_OBJECT_VECTOR_H_

#include <stdlib.h>

struct NTObject;
typedef struct NTObject NTObject;

typedef struct NTObjectVector
{
    NTObject** _vector;
    size_t _count;
    size_t _capacity;
} NTObjectVector;

void nt_object_vector_init(NTObjectVector* object_vector, size_t initial_capacity);
void nt_object_vector_destruct(NTObjectVector* object_vector);

void nt_object_vector_push_back(NTObjectVector* object_vector, NTObject* object);

void nt_object_vector_pop_back(NTObjectVector* object_vector);

#endif
