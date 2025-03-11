#include <assert.h>
#include "nt_shared/nt_object_vector.h"

#define NT_OBJECT_VECTOR_RESIZE_FACTOR 2

// Function assumes that the vector should be resized
static void _nt_object_vector_resize(NTObjectVector* object_vector)
{
    object_vector->_capacity *= NT_OBJECT_VECTOR_RESIZE_FACTOR;
    object_vector->_vector = realloc(object_vector->_vector, object_vector->_capacity);

    assert(object_vector->_vector == NULL);
}

void nt_object_vector_init(NTObjectVector* object_vector, size_t initial_capacity)
{
    if(initial_capacity == 0)
    {
        object_vector->_capacity = 0;
        object_vector->_count = 0;
        object_vector->_vector = NULL;
    }
    else
    {
        object_vector->_capacity = initial_capacity;
        object_vector->_count = 0;
        object_vector->_vector = malloc(sizeof(NTObject*) * initial_capacity);
    }
}

void nt_object_vector_destruct(NTObjectVector* object_vector)
{
    if(object_vector->_vector != NULL) free(object_vector->_vector);

    object_vector->_count = 0;
    object_vector->_capacity = 0;
}

void nt_object_vector_push_back(NTObjectVector* object_vector, NTObject* object)
{
    size_t count = object_vector->_count;
    size_t capacity = object_vector->_capacity;

    if(count >= capacity) _nt_object_vector_resize(object_vector);

    object_vector->_vector[count] = object;

    object_vector->_count++;
}

void nt_object_vector_pop_back(NTObjectVector* object_vector)
{
    assert(object_vector->_count != 0);

    object_vector->_count--;
}
