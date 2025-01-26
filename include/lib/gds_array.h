#ifndef GDS_ARRAY_H
#define GDS_ARRAY_H

#include <stdlib.h>

#define ARR_ERR_BASE 1000

/* Fields:
* size_t count - current count of elements,
* size_t max_count - array capacity,
* size_t element_size - size of each element,
* void* data - address of array beginning. */
struct GDSArray;

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Dynamically allocates memory for struct GDSArray and initializes it. Dynamically allocates max_count* element_size for array's data.
 * Return value:
 * on success - address of dynamically allocated struct GDSArray. 
 * on failure - NULL: max_count or element_size equals 0 OR malloc() failed for struct GDSArray or array's data. */
struct GDSArray* gds_arr_create(size_t max_count, size_t element_size);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Frees dynamically allocated memory for data. Sets values of array's fields to default values. If array == NULL, the function performs
 * no action. */
void gds_arr_destruct(struct GDSArray* array);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Calculates address of element with index specified by pos.
 * Return value:
 * on success: address of element with index specified by pos,
 * on failure: NULL. Function may fail if pos is invalid/out of bounds or if array is NULL. */
void* gds_arr_at(const struct GDSArray* array, size_t pos);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define ARR_ASSIGN_ERR_BASE (ARR_ERR_BASE + 10)
#define ARR_ASSIGN_ERR_ARR_NULL (ARR_ASSIGN_ERR_BASE + 1) // argument array is NULL.
#define ARR_ASSIGN_ERR_DATA_NULL (ARR_ASSIGN_ERR_BASE + 2) // argument data is NULL.
#define ARR_ASSIGN_ERR_POS_OUT_OF_BOUNDS (ARR_ASSIGN_ERR_BASE + 3) // argument pos is out of bounds(greater or equal to array->count)
#define ARR_ASSIGN_ERR_INVALID_ADDR_FOUND (ARR_ASSIGN_ERR_BASE + 4) // gds_arr_at() returned NULL.

/* Copies memory content pointed to by data into the array at index pos. Argument pos must be of lesser value than the count of the specified array's elements.
 * Function relies on gds_arr_at() to find the required address for the following memcpy() call.
 * Return value:
 * on success - 0,
 * on failure - one of the error codes above. */
int gds_arr_assign(struct GDSArray* array, size_t pos, const void* data);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define ARR_INSERT_ERR_BASE (ARR_ERR_BASE + 20)
#define ARR_INSERT_ERR_ARR_NULL (ARR_INSERT_ERR_BASE + 1) // argument array is NULL.
#define ARR_INSERT_ERR_DATA_NULL (ARR_INSERT_ERR_BASE + 2) // argument data is NULL.
#define ARR_INSERT_ERR_POS_OUT_OF_BOUNDS (ARR_ASSIGN_ERR_BASE + 3) // argument pos is out of bounds(greater or equal to array->count)
#define ARR_INSERT_ERR_SHIFTING_OP_FAILED (ARR_INSERT_ERR_BASE + 4) // internal function int _gds_arr_shift_right(struct GDSArray* array, size_t start_idx) failed.
#define ARR_INSERT_ERR_ASSIGN_FAIL (ARR_INSERT_ERR_BASE + 5) // gds_arr_assign() failed.

/* Inserts data pointed to by data to index pos in the array. Performs a call to _arr_shift_right() to make space for the new element at pos.
 * Performs a call to gds_arr_assign() to assign value at the pos index.
 * Return value:
 * on success - 0,
 * on failure - one of the error codes above. */
int gds_arr_insert(struct GDSArray* array, const void* data, size_t pos);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define ARR_APPEND_ERR_BASE (ARR_ERR_BASE + 30)
#define ARR_APPEND_ERR_ARR_NULL (ARR_APPEND_ERR_BASE + 1) // argument array is NULL.
#define ARR_APPEND_ERR_DATA_NULL (ARR_APPEND_ERR_BASE + 2) // argument data is NULL.
#define ARR_APPEND_ERR_ASSIGN_FAIL (ARR_APPEND_ERR_BASE + 5) // gds_arr_assign() failed.

/* Appends data pointed to by data to the end of the array. Performs the call: gds_arr_insert(array, data, array->count);
 * Return value:
 * on success - 0,
 * on failure - one of the error codes above. */
int gds_arr_append(struct GDSArray* array, const void* data);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define ARR_REMOVE_ERR_BASE (ARR_ERR_BASE + 40)
#define ARR_REMOVE_ERR_ARR_NULL (ARR_REMOVE_ERR_BASE + 1) // argument array is NULL.
#define ARR_REMOVE_ERR_SHIFTING_OP_FAILED (ARR_REMOVE_ERR_BASE + 2) // internal function int _gds_arr_shift_left(struct GDSArray* array, size_t start_idx) failed.
#define ARR_REMOVE_ERR_POS_OUT_OF_BOUNDS (ARR_REMOVE_ERR_BASE + 3) // argument pos is out of bounds(greater or equal to array->count)
/* Removes element with position pos from array.
 * Function relies on internal function _gds_arr_shift_left() which shifts elements right of pos(including) leftwards.
 * Return value:
 * on success - 0,
 * on failure - one of the error codes above. */
int gds_arr_remove(struct GDSArray* array, size_t pos);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define ARR_POP_ERR_BASE (ARR_ERR_BASE + 50)
#define ARR_POP_ERR_ARR_NULL (ARR_POP_ERR_BASE + 1) // argument array is NULL.
#define ARR_POP_ERR_ARR_EMPTY (ARR_POP_ERR_BASE + 3) // argument pos is out of bounds(greater or equal to array->count)
/* Removes last element in array by performing a call: gds_arr_remove(array, array->count - 1);
 * Return value:
 * on success - 0,
 * on failure - one of the error codes above. */
int gds_arr_pop(struct GDSArray* array);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define ARR_SET_SIZE_VAL_ERR_BASE (ARR_ERR_BASE + 70)

#define ARR_SET_SIZE_VAL_NULL_ARR (ARR_SET_SIZE_VAL_ERR_BASE + 1) // argument array is NULL
#define ARR_SET_SIZE_VAL_INVALID_NEW_COUNT_ARG (ARR_SET_SIZE_VAL_ERR_BASE + 3) // provided new_count argument is greater than the array's capacity
#define ARR_SET_SIZE_VAL_NULL_DEFAULT_VAL (ARR_SET_SIZE_VAL_ERR_BASE + 3) // function needs to expand the array but provided default_val arg is NULL.
#define ARR_SET_SIZE_VAL_ASSIGN_FAIL (ARR_SET_SIZE_VAL_ERR_BASE + 4) // expanding of array by repeated
                                                                     // calling gds_arr_assign(struct GDSArray* array, size_t pos, const void* data) failed.

/* Sets the count of elements of array to new_count. If the array's count is:
 * 1. greater than new_size - the array will be shrank to the new size.
 * 2. lesser than new_size - array will be expanded to the new size. This means that elements will be appended to the end of the array until array->count = new_count.
 * Content of memory pointed at by default_val parameter will determine the value of these elements.
 * 3. equal to new_size - array will remain unchanged.
 * If the function is guaranteed to shrink the array, argument default_val may be NULL.
 * Return value:
 * on success: 0,
 * on failure: one of the error codes above. */
int gds_arr_set_size_val(struct GDSArray* array, size_t new_count, void* default_val);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define ARR_SET_SIZE_GEN_ERR_BASE (ARR_ERR_BASE + 70)

#define ARR_SET_SIZE_GEN_NULL_ARR (ARR_SET_SIZE_GEN_ERR_BASE + 1) // argument array is NULL
#define ARR_SET_SIZE_GEN_INVALID_NEW_COUNT_ARG (ARR_SET_SIZE_GEN_ERR_BASE + 3) // provided new_count argument is greater than the array's capacity
#define ARR_SET_SIZE_GEN_NULL_GEN_FUNC (ARR_SET_SIZE_GEN_ERR_BASE + 3) // function needs to expand the array but provided el_gen_func() arg is NULL.
#define ARR_SET_SIZE_GEN_ASSIGN_FAIL (ARR_SET_SIZE_GEN_ERR_BASE + 4) // expanding of array by repeated
                                                                     // calling gds_arr_assign(struct GDSArray* array, size_t pos, const void* data) failed.

/* Sets the count of elements of array to new_count. If the array's count is:
 * 1. greater than new_size - the array will be shrank to the new size.
 * 2. lesser than new_size - array will be expanded to the new size. This means that elements will be appended to the end of the array until array->count = new_count.
 * As opposed to gds_arr_set_size_val() func(which will append the same data n times),
 * This function will generate a new element and append it at the end(by calling the el_gen_func) n times. This may be useful in situations where elements of the array
 * are complex and involve malloc() calls. The el_gen_func(void* data) must return a pointer to a dynamically alloced block of memory. The parameter may be used as the user likes.
 * 3. equal to new_size - array will remain unchanged.
 * If the function is guaranteed to shrink the array, argument default_val may be NULL.
 * Return value:
 * on success: 0,
 * on failure: one of the error codes above. */
int gds_arr_set_size_gen(struct GDSArray* array, size_t new_count, void* (*el_gen_func)(void* data), void* data);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Empties the array.
 * Return value:
 * on success: 0,
 * on failure: 1 - argument 'array' is null. */
int gds_arr_empty(struct GDSArray* array);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define ARR_REALLOC_ERR_BASE (ARR_ERR_BASE + 60)
#define ARR_REALLOC_ERR_ARR_NULL (ARR_REALLOC_ERR_BASE + 1)
#define ARR_REALLOC_ERR_NEW_COUNT_EQ_ZERO (ARR_REALLOC_ERR_BASE + 2)
#define ARR_REALLOC_ERR_REALLOC_FAIL (ARR_REALLOC_ERR_BASE + 3)

/* Performs a realloc() on array's data, so the new data can fit new_max_count elements. If count > new_max_count, the array will shrink.
 * Return value:
 * on success - 0,
 * on failure - one of the error codes above. */
int gds_arr_realloc(struct GDSArray* array, size_t new_max_count);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Gets current count of elements in array.
 * Return value:
 * on success: current count of elements in array, 
 * on failure: -1 - array is NULL. */
ssize_t gds_arr_get_count(const struct GDSArray* array);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Gets max count of elements in array.
 * Return value:
 * on success: max count of elements in array, 
 * on failure: -1 - array is NULL. */
ssize_t gds_arr_get_max_count(const struct GDSArray* array);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Gets address of data in array.
 * Return value:
 * on success: address of array's data field,
 * on failure: NULL - array is NULL.*/
void* gds_arr_get_data(const struct GDSArray* array);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Performs sizeof(struct GDSArray) and returns the value */
size_t gds_arr_get_struct_size();

// --------------------------------------------------------------------------------------------------------------------------------------------

#endif
