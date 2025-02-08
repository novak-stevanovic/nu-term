#ifndef GDS_VECTOR_H
#define GDS_VECTOR_H

#include <stdlib.h>

#define VEC_ERR_BASE 0

#define DEFAULT_SIZE_COUNT 50
#define DEFAULT_RESIZE_COUNT 25

#ifdef GDS_DISABLE_OPAQUE_STRUCTS
typedef struct
{
    size_t _count;
    size_t _alloced_count;
    size_t _count_in_chunk;
    size_t _element_size;
    size_t _min_count;
    void* _data;
    void (*_on_element_removal_func)(void*);
} GDSVector;
#else
typedef struct GDSVector GDSVector;
#endif

/* Fields:
* 1 - size_t count - current count of elements,
* 2 - size_t alloced_count - current array capacity,
* 3 - size_t count_in_chunk - number of elements in each chunk - how much the array resizes on realloac.
* 4 - size_t element_size - size of 1 element in array,
* 5 - size_t min_count - initial vector capacity. The vector->data field will always have capacity for min_count count of elements,
* 6 - void* data - ptr to data(the vector itself). 
* 7 - void on_element_removal_func(void*) - pointer to a callback function that is called on element removal, for each removed element.
    * void* parameter - a pointer to the element stored in the vector. Note:
    * - The vector may store pointers to dynamically allocated objects. This function can be used 
    *   to properly free the memory of elements removed from the vector.
    * - In this case, the `void*` parameter represents a pointer to an element inside the vector,
    *   which itself is a pointer to a dynamically allocated object */

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Allocates memory for GDSVector vector, initializes fields. Allocates the memory for the first min_count elements of the array.
 * Keep in mind that: min_count, count_in_chunk and element_size parameters must all be greater than 0.
 * Return value:
 * on success: address of dynamically allocated GDSVector. 
 * on failure: NULL - count_in_chunk, element_size or min_count equal to 0 or malloc() failed for either GDSVector or vector data. */
GDSVector* gds_vec_create(size_t min_count, size_t count_in_chunk, size_t element_size, void (*on_element_removal_func)(void*));

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Initializes vector's fields. Dynamically allocates the memory for the first min_count elements of the array.
 * Keep in mind that: min_count, count_in_chunk and element_size parameters must all be greater than 0.
 * Return value:
 * on success: 0,
 * on failure: 1, vector parameter is NULL, 2 - count_in_chunk, element_size or min_count equal to 0, 
 * 3 - malloc() failed for vector's data. */
#ifdef GDS_DISABLE_OPAQUE_STRUCTS
int gds_vec_init(GDSVector* vector, size_t min_count, size_t count_in_chunk, size_t element_size, void (*on_element_removal_func)(void*));
#endif

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Frees dynamically allocated memory. Sets fields to default values. If vector == NULL, the function performs no action. */
void gds_vec_destruct(GDSVector* vector);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Calculates address of element with index specified by pos.
 * Return value:
 * on success: address of element with index pos,
 * on failure: NULL. Function may fail if: vector == null or pos >= vector->count. */
void* gds_vec_at(const GDSVector* vector, size_t pos);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define VEC_ASSIGN_ERR_BASE (VEC_ERR_BASE + 10)

#define VEC_ASSIGN_ERR_NULL_VEC (VEC_ASSIGN_ERR_BASE + 1) // argument vector equals to NULL
#define VEC_ASSIGN_ERR_NULL_DATA (VEC_ASSIGN_ERR_BASE + 2) // argument data equals to NULL
#define VEC_ASSIGN_ERR_POS_OUT_OF_BOUNDS (VEC_ASSIGN_ERR_BASE + 3) // arugment pos is not of lesser value than vector->count
#define _VEC_ASSIGN_FERR_INVALID_ADDR_FOUND (VEC_ASSIGN_ERR_BASE + 4) // internal func _gds_vec_get_element_addr() returned NULL.

/* Assigns data pointed to by data to position pos inside vector. Keep in mind that the maximum value of pos must be vector->count - 1. Function relies on gds_vec_at()
 * to find the required address for the following memcpy() call.
 * Return value:
 * on success: 0,
 * on failure: one of the error codes above. */
int gds_vec_assign(GDSVector* vector, const void* data, size_t pos);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define VEC_INSERT_ERR_BASE (VEC_ERR_BASE + 20)

#define VEC_INSERT_ERR_NULL_VEC (VEC_INSERT_ERR_BASE + 1) // argument vector equals to NULL
#define VEC_INSERT_ERR_NULL_DATA (VEC_INSERT_ERR_BASE + 2) // argument data equals to NULL
#define VEC_INSERT_ERR_POS_OUT_OF_BOUNDS (VEC_INSERT_ERR_BASE + 3) // arugment pos is of greater value than vector->count.
#define VEC_INSERT_FERR_RESIZE_OP_FAILED (VEC_INSERT_ERR_BASE + 4) // internal function _vec_resize() failed.
#define _VEC_INSERT_FERR_SHIFTING_OP_FAILED (VEC_INSERT_ERR_BASE + 4) // internal function _gds_vec_shift_right() failed.
#define _VEC_INSERT_FERR_ASSIGN_OP_FAILED (VEC_INSERT_ERR_BASE + 5) // function gds_vec_assign() failed.

/* Inserts element pointed at by data at index pos in the vector. May result in resizing of vector. Performs a call to _gds_vec_shift_right() to 
 * make space for the new element at pos. Performs a call to gds_vec_assign() to assign value to position of new element.
 * Return value:
 * on success: 0,
 * on failure: one of the error codes above. */
int gds_vec_insert(GDSVector* vector, const void* data, size_t pos);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define VEC_APPEND_ERR_BASE (VEC_ERR_BASE + 30)

#define VEC_APPEND_ERR_NULL_VEC (VEC_APPEND_ERR_BASE + 1) // argument vector equals to NULL
#define VEC_APPEND_ERR_NULL_DATA (VEC_APPEND_ERR_BASE + 2) // argument data equals to NULL
#define VEC_APPEND_FERR_RESIZE_OP_FAILED (VEC_APPEND_ERR_BASE + 4) // internal function _gds_vec_resize() failed.
#define _VEC_APPEND_FERR_ASSIGN_OP_FAILED (VEC_APPEND_ERR_BASE + 5) // function gds_vec_assign() failed.

/* Appends data pointed at by data at the end of the vector. Calls gds_vec_insert() by specyfing pos as vector->count.
 * May result in resizing of vector.
 * Return value:
 * on success: 0,
 * on failure: one of the error codes above. */
int gds_vec_append(GDSVector* vector, const void* data);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define VEC_REMOVE_ERR_BASE (VEC_ERR_BASE + 40)

#define VEC_REMOVE_ERR_NULL_VEC (VEC_REMOVE_ERR_BASE + 1) // argument vector equals to NULL
#define VEC_REMOVE_ERR_POS_OUT_OF_BOUNDS (VEC_REMOVE_ERR_BASE + 2) // arugment pos is of greater value than vector->count.
#define _VEC_REMOVE_FERR_SHIFTING_OP_FAILED (VEC_REMOVE_ERR_BASE + 3) // internal function _gds_vec_shift_left() failed.
#define VEC_REMOVE_FERR_RESIZE_OP_FAILED (VEC_REMOVE_ERR_BASE + 4) // internal function _gds_vec_resize() failed.
#define _VEC_REMOVE_FERR_AT_FAILED (VEC_REMOVE_ERR_BASE + 5) // call to gds_vec_at() returned NULL.

/* Removes element at index pos in vector. May result in resizing of vector. Function shifts the elements right of(including) pos leftwards by
 * calling _gds_vec_shift_left().
 * Return value:
 * on success: 0,
 * on failure: one of the error codes above. */
int gds_vec_remove(GDSVector* vector, size_t pos);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define VEC_POP_ERR_BASE (VEC_ERR_BASE + 50)

#define VEC_POP_ERR_NULL_VEC (VEC_POP_ERR_BASE + 1) // argument vector equals to NULL
#define VEC_POP_ERR_VEC_EMPTY (VEC_POP_ERR_BASE + 2) // arugment pos is of greater value than vector->count.
#define VEC_POP_FERR_RESIZE_OP_FAILED (VEC_POP_ERR_BASE + 4) // internal function _gds_vec_resize() failed.
#define _VEC_POP_FERR_AT_FAILED (VEC_POP_ERR_BASE + 5) // call to gds_vec_at() returned NULL.

/* Removes last element of vector. May result in resizing of vector. Performs a call to gds_vec_remove(vector, vector->count - 1).
 * Return value:
 * on success: 0,
 * on failure: one of the error codes above. */
int gds_vec_pop(GDSVector* vector);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define VEC_SET_SIZE_ERR_BASE (VEC_ERR_BASE + 60)

#define VEC_SET_SIZE_ERR_NULL_VEC (VEC_SET_SIZE_ERR_BASE + 1) // argument vector is NULL
#define VEC_SET_SIZE_ERR_RESIZE_FAIL (VEC_SET_SIZE_ERR_BASE + 2) // resizing(reallocing) of vector failed.
#define VEC_SET_SIZE_ERR_NULL_ASSIGN_FUNC (VEC_SET_SIZE_ERR_BASE + 3) // function needs to expand the vector but provided assign_func() is NULL.
#define _VEC_SET_SIZE_FERR_AT_FAIL (VEC_SET_SIZE_ERR_BASE + 4) // one of the calls to gds_vec_at() failed.

/* Sets the count of elements of vector to new_count. If the vector's count is:
 * 1. greater than new_size - the vector will be shrank to the new size.
 * 2. lesser than new_size - vector will be expanded to the new size. This means that the provided function assign_func() will be called repeatedly(for each
 * element added) until vector->count = new_count. This function accepts 2 params: 1. address of the newly-added element in the vector, 2. address of the data argument.
 * This allows the caller of the function to perform some action on the chunk of memory in the vector, for each newly-added element(initializing, assigning value... etc).
 * Data parameter allows the caller to pass data into the assign_func.
 * 3. equal to new_size - vector will remain unchanged.
 * Keep in mind that the performance of this function is much better than appending elements one by one to the end of the vector. This is only one realloc() will be
 * performed(if needed), as opposed to potentially more realloc() calls.
 * If the function is guaranteed to shrink the vector, argument default_val may be NULL. If the current alloced_count for the given vector is lesser than new_count, vector will
 * attempt to perform a realloc() call so it is able to fit all the elements.
 * Return value:
 * on success: 0,
 * on failure: one of the error codes above. */
int gds_vec_set_size(GDSVector* vector, size_t new_size, void (*assign_func)(void*, void*), void* data);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Empties the vector by calling gds_vec_set_size(vector, 0, NULL);
 * Return value:
 * on success: 0,
 * on failure: 1 - argument 'vector' is null, 2 - gds_vec_set_size() failed. */
int gds_vec_empty(GDSVector* vector);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Returns current count of elements in vector.
 * Return value:
 * on success: count of elements in vector. 
 * on failure: -1 - vector is NULL. */
ssize_t gds_vec_get_count(const GDSVector* vector);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Returns current resize count of vector.
 * on success: vector's count_in_chunk field. 
 * on failure: -1 - vector is NULL. */
ssize_t gds_vec_get_resize_count(const GDSVector* vector);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Sets resize count(count_in_chunk field) of vector. This will resize the vector according to the new count_in_chunk value.
 * This will impact future resizing operations.
 * Return value:
 * on success: 0,
 * on failure: -1 - vector is NULL. -2 - _gds_vec_resize(GDSVector* vector, size_t chunk_count) failed. */
int gds_vec_set_resize_count(GDSVector* vector, size_t count_in_chunk);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Sets min_count of vector. This will resize the vector to accomodate for the new min_count.
 * Return value:
 * on success: 0,
 * on failure: -1 - vector is NULL. -2 - _gds_vec_resize(GDSVector* vector, size_t chunk_count) failed. */
ssize_t gds_vec_set_min_count(GDSVector* vector, size_t new_min_count);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Gets vector's min_count.
 * Return value:
 * on success: non-negative value equal to vector's min_count field,
 * on failure: -1, argument vector is NULL. */
ssize_t gds_vec_get_min_count(const GDSVector* vector);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Returns address of data in vector.
 * Return value: 
 * on success: address of vector->data.
 * on failure: NULL - vector is null. */
void* gds_vec_get_data(const GDSVector* vector);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Returns value of vector's element_size field.
 * Return value:
 * on success: value greater than 0, representing the vector's element_size field,
 * on failure: 0 - argument vector is NULL. */
size_t gds_vec_get_element_size(const GDSVector* vector);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Performs sizeof(GDSVector) and returns the value. */
size_t gds_vec_get_struct_size();

// --------------------------------------------------------------------------------------------------------------------------------------------

#endif
