#include "nt_shared/nt_object_vector.h"

void nt_object_vector_init(NTObjectVector* vector)
{
    vector = nt_vector_create(10, 10, 10, NULL);
}
void nt_object_vector_append(NTObjectVector* vector, struct NTObject* obj)
{
}
void nt_object_vector_insert(NTObjectVector* vector)
{
}

