#ifndef GDS_ARRAY_H
#define GDS_ARRAY_H

#include <stdlib.h>
#include "gds.h"

#define ARR_ERR_BASE 1000

#ifdef GDS_DISABLE_OPAQUE_STRUCTS
typedef struct GDSArray
{
    size_t _count;
    size_t _max_count;
    size_t _element_size;
    void* _data;
    void (*_on_element_removal_func)(void*);
} GDSArray;
#else
typedef struct GDSArray GDSArray;
#endif

/* Fields:
* size_t count - current count of elements,
* size_t max_count - array capacity,
* size_t element_size - size of each element,
* void* data - address of array beginning.
* void on_element_removal_func(void*) - pointer to a callback function that is called on element removal, for each removed element.
    * void* parameter - a pointer to the element stored in the array. Note:
    * - The array may store pointers to dynamically allocated objects. This function can be used 
    *   to properly free the memory of elements removed from the array.
    * - In this case, the `void*` parameter represents a pointer to an element inside the array,
    *   which itself is a pointer to a dynamically allocated object */


// --------------------------------------------------------------------------------------------------------------------------------------------

/* Dynamically allocates memory for GDSArray and initializes it. Dynamically allocates max_count * element_size for array's data.
 * Return value:
 * on success - address of dynamically allocated GDSArray. 
 * on failure - NULL: max_count or element_size equals 0 OR malloc() failed for GDSArray or array's data. */
GDSArray* gds_arr_create(size_t max_count, size_t element_size, void (*on_element_removal_func)(void*));

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Initializes GDSArray array. Used when opaque structs are disabled. Dynamically allocates max_count * element_size for array's data. 
 * Return value:
 * on success - 0,
 * on failure - 1 - array param is NULL, 2 - max_count or element_size is 0, 3 - malloc() for array's data failed. */
#ifdef GDS_DISABLE_OPAQUE_STRUCTS
int gds_arr_init(GDSArray* array, size_t max_count, size_t element_size, void (*on_element_removal_func)(void*));
#endif

// --------------------------------------------------------------------------------------------------------------------------------------------
/* Frees dynamically allocated memory for data. Sets values of array's fields to default values. If array == NULL, the function performs no action. */
void gds_arr_destruct(GDSArray* array);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Calculates address of element with index specified by pos.
 * Return value:
 * on success: address of element with index specified by pos,
 * on failure: NULL. Function may fail if pos is invalid/out of bounds or if array is NULL. */
void* gds_arr_at(const GDSArray* array, size_t pos);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define ARR_ASSIGN_ERR_BASE (ARR_ERR_BASE + 10)

#define ARR_ASSIGN_ERR_ARR_NULL (ARR_ASSIGN_ERR_BASE + 1) // argument array is NULL.
#define ARR_ASSIGN_ERR_DATA_NULL (ARR_ASSIGN_ERR_BASE + 2) // argument data is NULL.
#define ARR_ASSIGN_ERR_POS_OUT_OF_BOUNDS (ARR_ASSIGN_ERR_BASE + 3) // argument pos is out of bounds(greater or equal to array->count)
#define _ARR_ASSIGN_ERR_INVALID_ADDR_FOUND (ARR_ASSIGN_ERR_BASE + 4) // gds_arr_at() returned NULL.

/* Copies memory content pointed to by data into the array at index pos. Argument pos must be of lesser value than the count of the specified array's elements.
 * Function relies on gds_arr_at() to find the required address for the following memcpy() call.
 * Return value:
 * on success - 0,
 * on failure - one of the error codes above. */
int gds_arr_assign(GDSArray* array, size_t pos, const void* data);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define ARR_INSERT_ERR_BASE (ARR_ERR_BASE + 20)

#define ARR_INSERT_ERR_ARR_NULL (ARR_INSERT_ERR_BASE + 1) // argument array is NULL.
#define ARR_INSERT_ERR_DATA_NULL (ARR_INSERT_ERR_BASE + 2) // argument data is NULL.
#define ARR_INSERT_ERR_POS_OUT_OF_BOUNDS (ARR_ASSIGN_ERR_BASE + 3) // argument pos is out of bounds(greater or equal to array->count)
#define _ARR_INSERT_FERR_SHIFTING_OP_FAILED (ARR_INSERT_ERR_BASE + 4) // internal function _gds_arr_shift_right() failed.
#define _ARR_INSERT_FERR_ASSIGN_FAIL (ARR_INSERT_ERR_BASE + 5) // gds_arr_assign() failed.
#define ARR_INSERT_ERR_INSUFF_SPACE (ARR_INSERT_ERR_BASE + 6) // Occurrs when array->count == array->max_count

/* Inserts data pointed to by data to index pos in the array. Performs a call to _arr_shift_right() to make space for the new element at pos.
 * Performs a call to gds_arr_assign() to assign value at the pos index.
 * Return value:
 * on success - 0,
 * on failure - one of the error codes above. */
int gds_arr_insert(GDSArray* array, const void* data, size_t pos);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define ARR_APPEND_ERR_BASE (ARR_ERR_BASE + 30)

#define ARR_APPEND_ERR_ARR_NULL (ARR_APPEND_ERR_BASE + 1) // argument array is NULL.
#define ARR_APPEND_ERR_DATA_NULL (ARR_APPEND_ERR_BASE + 2) // argument data is NULL.
#define ARR_APPEND_ERR_ASSIGN_FAIL (ARR_APPEND_ERR_BASE + 5) // gds_arr_assign() failed.
#define ARR_APPEND_ERR_INSUFF_SPACE (ARR_APPEND_ERR_BASE + 6) // Occurrs when array->count == array->max_count

/* Appends data pointed to by data to the end of the array. Performs the call: gds_arr_insert(array, data, array->count);
 * Return value:
 * on success - 0,
 * on failure - one of the error codes above. */
int gds_arr_append(GDSArray* array, const void* data);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define ARR_REMOVE_ERR_BASE (ARR_ERR_BASE + 40)

#define ARR_REMOVE_ERR_ARR_NULL (ARR_REMOVE_ERR_BASE + 1) // argument array is NULL.
#define _ARR_REMOVE_FERR_SHIFTING_OP_FAILED (ARR_REMOVE_ERR_BASE + 2) // internal function _gds_arr_shift_left() failed.
#define ARR_REMOVE_ERR_POS_OUT_OF_BOUNDS (ARR_REMOVE_ERR_BASE + 3) // argument pos is out of bounds(greater or equal to array->count)
#define _ARR_REMOVE_FERR_AT_FAIL (ARR_REMOVE_ERR_BASE + 4) // call to gds_arr_at() returned NULL.

/* Removes element with position pos from array.
 * Function relies on internal function _gds_arr_shift_left() which shifts elements right of pos(including) leftwards.
 * Return value:
 * on success - 0,
 * on failure - one of the error codes above. */
int gds_arr_remove(GDSArray* array, size_t pos);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define ARR_POP_ERR_BASE (ARR_ERR_BASE + 50)
#define ARR_POP_ERR_ARR_NULL (ARR_POP_ERR_BASE + 1) // argument array is NULL.
#define ARR_POP_ERR_ARR_EMPTY (ARR_POP_ERR_BASE + 3) // argument pos is out of bounds(greater or equal to array->count)

/* Removes last element in array by performing a call: gds_arr_remove(array, array->count - 1);
 * Return value:
 * on success - 0,
 * on failure - one of the error codes above. */
int gds_arr_pop(GDSArray* array);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define ARR_SET_SIZE_ERR_BASE (ARR_ERR_BASE + 70)

#define ARR_SET_SIZE_ERR_NULL_ARR (ARR_SET_SIZE_ERR_BASE + 1) // argument array is NULL
#define ARR_SET_SIZE_ERR_INVALID_NEW_COUNT_ARG (ARR_SET_SIZE_ERR_BASE + 3) // provided new_count argument is greater than the array's capacity
#define ARR_SET_SIZE_ERR_NULL_ASSIGN_FUNC (ARR_SET_SIZE_ERR_BASE + 3) // function needs to expand the array but provided assign_func is NULL.
#define _ARR_SET_SIZE_FERR_AT_FAIL (ARR_SET_SIZE_ERR_BASE + 4) // one of the calls to gds_array_at() failed.
#define _ARR_SET_SIZE_ERR_ON_BATCH_REMOVAL_FAIL (ARR_SET_SIZE_ERR_BASE + 5) // internal function failed: _gds_arr_on_element_removal_batch()

/* Sets the count of elements of array to new_count. If the array's count is:
 * 1. greater than new_size - the array will be shrank to the new size.
 * 2. lesser than new_size - array will be expanded to the new size. This means that the provided function assign_func() will be called repeatedly(for each
 * element added) until array->count = new_count. This function accepts 2 params: 1. address of the newly-added element in the array, 2. address of the data argument.
 * This allows the caller of the function to perform some action on the chunk of memory in the array, for each newly-added element(initializing, assigning value... etc).
 * Data parameter allows the caller to pass data into the assign_func.
 * 3. equal to new_size - array will remain unchanged.
 * If the function is guaranteed to shrink the array, argument default_val may be NULL.
 * Return value:
 * on success: 0,
 * on failure: one of the error codes above. */
int gds_arr_set_size(GDSArray* array, size_t new_count, void (*assign_func)(void*, void*), void* data);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Empties the array by calling gds_arr_set_size(array, 0, NULL).
 * Return value:
 * on success: 0,
 * on failure: 1 - argument 'array' is null. 2 - invoked function failed. */
int gds_arr_empty(GDSArray* array);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define ARR_REALLOC_ERR_BASE (ARR_ERR_BASE + 60)
#define ARR_REALLOC_ERR_ARR_NULL (ARR_REALLOC_ERR_BASE + 1)
#define ARR_REALLOC_ERR_NEW_COUNT_EQ_ZERO (ARR_REALLOC_ERR_BASE + 2)
#define ARR_REALLOC_ERR_REALLOC_FAIL (ARR_REALLOC_ERR_BASE + 3)

/* Performs a realloc() on array's data, so the new data can fit new_max_count elements. If count > new_max_count, the array will shrink.
 * Keep in mind that this will not perform any calls to array->on_element_removal_func(void*). Use a variant of gds_arr_set_size() instead.
 * Return value:
 * on success - 0,
 * on failure - one of the error codes above. */
int gds_arr_realloc(GDSArray* array, size_t new_max_count);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Gets current count of elements in array.
 * Return value:
 * on success: current count of elements in array, 
 * on failure: -1 - array is NULL. */
ssize_t gds_arr_get_count(const GDSArray* array);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Gets max count of elements in array.
 * Return value:
 * on success: max count of elements in array, 
 * on failure: -1 - array is NULL. */
ssize_t gds_arr_get_max_count(const GDSArray* array);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Gets address of data in array.
 * Return value:
 * on success: address of array's data field,
 * on failure: NULL - array is NULL.*/
void* gds_arr_get_data(const GDSArray* array);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Returns element size of array.
 * Return value:
 * on success: value greater than 0, representing the value of element_size field in array,
 * on failure: 0 - argument array is NULL. */
size_t gds_arr_get_element_size(const GDSArray* array);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Performs sizeof(GDSArray) and returns the value */
size_t gds_arr_get_struct_size();

// --------------------------------------------------------------------------------------------------------------------------------------------

#endif
