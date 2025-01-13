#ifndef GENDS_VECTOR_H
#define GENDS_VECTOR_H

#include <stdlib.h>

#define VEC_ERR_BASE 0

#define DEFAULT_SIZE_COUNT 50
#define DEFAULT_RESIZE_COUNT 25

/* Fields:
* size_t count - current count of elements,
* size_t alloced_count - current array capacity,
* size_t chunk_count - number of elements in each chunk - how much the array resizes on realloac.
* size_t element_size - size of 1 element in array,
* size_t min_count - initial vector capacity. The vector->data field will always have capacity for min_count count of elements,
* void* data - ptr to data(the vector itself). */
struct Vector;

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Allocates memory for struct Vector vector, initializes struct fields. Allocates the memory for the first min_count elements of the array. 
 * Return value:
 * on success: address of dynamically allocated struct Vector. 
 * on failure: NULL - chunk_count or element_size equal to 0 or malloc() failed for either struct Vector or vector data. */
struct Vector* vec_init(size_t min_count, size_t chunk_count, size_t element_size);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Calls vec_init with parameters chunk_count = DEFAULT_RESIZE_COUNT and min_SIZE = DEFAULT_SIZE_COUNT */
#define VEC_INIT_DEFAULT(vector, element_size) vec_init(DEFAULT_SIZE_COUNT, DEFAULT_RESIZE_COUNT, element_size)

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Frees dynamically allocated memory. Sets fields to default values. If vector == NULL, the function performs no action. */
void vec_destruct(struct Vector* vector);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Calculates address of element with index specified by pos.
 * Return value:
 * on success: address of element with index pos,
 * on failure: NULL. Function may fail if: vector == null or pos >= vector->count. */
void* vec_at(const struct Vector* vector, size_t pos);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define VEC_ASSIGN_ERR_BASE (VEC_ERR_BASE + 10)

#define VEC_ASSIGN_ERR_NULL_VEC (VEC_ASSIGN_ERR_BASE + 1) // argument vector equals to NULL
#define VEC_ASSIGN_ERR_NULL_DATA (VEC_ASSIGN_ERR_BASE + 2) // argument data equals to NULL
#define VEC_ASSIGN_ERR_POS_OUT_OF_BOUNDS (VEC_ASSIGN_ERR_BASE + 3) // arugment pos is not of lesser value than vector->count
#define VEC_ASSIGN_ERR_INVALID_ADDR_FOUND (VEC_ASSIGN_ERR_BASE + 4) // internal func _vec_get_element_addr(struct Vector* vec, size_t pos) returned NULL.

/* Assigns data pointed to by data to position pos inside Vector vector. Keep in mind that the maximum value of pos must be vector->count - 1. Function relies on vec_at()
 * to find the required address for the following memcpy() call.
 * Return value:
 * on success: 0,
 * on failure: one of the error codes above. */
int vec_assign(struct Vector* vector, const void* data, size_t pos);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define VEC_INSERT_ERR_BASE (VEC_ERR_BASE + 20)

#define VEC_INSERT_ERR_NULL_VEC (VEC_INSERT_ERR_BASE + 1) // argument vector equals to NULL
#define VEC_INSERT_ERR_NULL_DATA (VEC_INSERT_ERR_BASE + 2) // argument data equals to NULL
#define VEC_INSERT_ERR_POS_OUT_OF_BOUNDS (VEC_INSERT_ERR_BASE + 3) // arugment pos is of greater value than vector->count.
#define VEC_INSERT_ERR_RESIZE_OP_FAILED (VEC_INSERT_ERR_BASE + 4) // internal function _vec_resize(struct Vector* vector, size_t chunks_required) failed.
#define VEC_INSERT_ERR_SHIFTING_OP_FAILED (VEC_INSERT_ERR_BASE + 4) // internal function _vec_shift_right(struct Vector* vector, size_t start_idx) failed.
#define VEC_INSERT_ERR_ASSIGN_OP_FAILED (VEC_INSERT_ERR_BASE + 5) // function vec_assign(struct Vector* vector, const void* data, size_t pos) failed.

/* Inserts element pointed at by data at index pos in the Vector vector. May result in resizing of vector. Performs a call to _vec_shift_right() to 
 * make space for the new element at pos. Performs a call to vec_assign() to assign value to position of new element.
 * Return value:
 * on success: 0
 * on failure: one of the error codes above. */
int vec_insert(struct Vector* vector, const void* data, size_t pos);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define VEC_APPEND_ERR_BASE (VEC_ERR_BASE + 30)

#define VEC_APPEND_ERR_NULL_VEC (VEC_APPEND_ERR_BASE + 1) // argument vector equals to NULL
#define VEC_APPEND_ERR_NULL_DATA (VEC_APPEND_ERR_BASE + 2) // argument data equals to NULL
#define VEC_APPEND_ERR_RESIZE_OP_FAILED (VEC_APPEND_ERR_BASE + 4) // internal function _vec_resize(struct Vector* vector, size_t chunks_required) failed.
#define VEC_APPEND_ERR_ASSIGN_OP_FAILED (VEC_APPEND_ERR_BASE + 5) // function vec_assign(struct Vector* vector, const void* data, size_t pos) failed.

/* Appends data pointed at by data at the end of the Vector vector. Calls vec_insert() by specyfing pos as vector->count.
 * May result in resizing of vector.
 * Return value:
 * on success: 0
 * on failure: one of the error codes above. */
int vec_append(struct Vector* vector, const void* data);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define VEC_REMOVE_ERR_BASE (VEC_ERR_BASE + 40)

#define VEC_REMOVE_ERR_NULL_VEC (VEC_REMOVE_ERR_BASE + 1) // argument vector equals to NULL
#define VEC_REMOVE_ERR_POS_OUT_OF_BOUNDS (VEC_REMOVE_ERR_BASE + 2) // arugment pos is of greater value than vector->count.
#define VEC_REMOVE_ERR_SHIFTING_OP_FAILED (VEC_REMOVE_ERR_BASE + 3) // internal function _vec_shift_left(struct Vector* vector, size_t start_idx) failed.
#define VEC_REMOVE_ERR_RESIZE_OP_FAILED (VEC_REMOVE_ERR_BASE + 4) // internal function _vec_resize(struct Vector* vector, size_t chunks_required) failed.

/* Removes element at index pos in Vector vector. May result in resizing of vector. Function shifts the elements right of(including) pos leftwards by calling _vec_shift_left().
 * Return value:
 * on success: 0
 * on failure: one of the error codes above. */
int vec_remove(struct Vector* vector, size_t pos);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define VEC_POP_ERR_BASE (VEC_ERR_BASE + 50)

#define VEC_POP_ERR_NULL_VEC (VEC_POP_ERR_BASE + 1) // argument vector equals to NULL
#define VEC_POP_ERR_VEC_EMPTY (VEC_POP_ERR_BASE + 2) // arugment pos is of greater value than vector->count.
#define VEC_POP_ERR_RESIZE_OP_FAILED (VEC_POP_ERR_BASE + 4) // internal function _vec_resize(struct Vector* vector, size_t chunks_required) failed.

/* Removes last element Vector vector. May result in resizing of vector. Performs a call to vec_remove(vector, vector->count - 1).
 * Return value:
 * on success: 0
 * on failure: one of the error codes above. */
int vec_pop(struct Vector* vector);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Empties the vector.
 * Return value:
 * on success: 0,
 * on failure: 1 - argument 'vector' is null, 2 - internal function _vec_resize() failed. */
int vec_empty(struct Vector* vector);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Returns current count of elements in vector.
 * Return value:
 * on success: count of elements in vector. 
 * on failure: -1 - vector is NULL. */
ssize_t vec_get_count(const struct Vector* vector);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Returns current resize count of vector. */
ssize_t vec_get_resize_count(const struct Vector* vector);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Sets resize count of vector. This will impact resizing operations.
 * Return value:
 * on success: count of elements in vector. 
 * on failure: -1 - vector is NULL. */
int vec_set_resize_count(struct Vector* vector, size_t chunk_count);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Returns address of data in vector.
 * Return value: 
 * on success: address of vector->data.
 * on failure: NULL - vector is null. */
void* vec_get_data(const struct Vector* vector);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Performs sizeof(struct Vector) and returns the value. */
size_t vec_get_struct_size();

// --------------------------------------------------------------------------------------------------------------------------------------------

#endif
