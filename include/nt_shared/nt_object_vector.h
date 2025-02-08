#ifndef NT_OBJECT_VECTOR_H
#define NT_OBJECT_VECTOR_H

#include "api/nt_vec_api.h"

struct NTObject;

typedef NTVector NTObjectVector;

void nt_object_vector_init(NTObjectVector* vector);
void nt_object_vector_append(NTObjectVector* vector, struct NTObject* obj);
void nt_object_vector_insert(NTObjectVector* vector); 

#endif
