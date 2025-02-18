#ifndef _GDS_ARRAY_H_
#define _GDS_ARRAY_H_

#include <stdlib.h>
#include <stdbool.h>

#include "gds.h"

#ifdef GDS_ENABLE_OPAQUE_STRUCTS
struct GDSArray;
#else
#define __GDS_ARRAY_DEF_ALLOW__
#include "def/gds_array_def.h"
#endif

typedef struct GDSArray GDSArray;

// ------------------------------------------------------------------------------------------------------------------------------------------

#define GDS_ARR_ERR_BASE 100
#define GDS_ARR_ERR_INSUFF_CAPACITY 101
#define GDS_ARR_ERR_ARR_EMPTY 102
#define GDS_ARR_ERR_MALLOC_FAIL 103
#define GDS_ARR_ERR_REALLOC_FAIL 104

// ------------------------------------------------------------------------------------------------------------------------------------------

/* Initializes array. Used when opaque structs are disabled. May also be used for initializing
 * an array after its destruction. Dynamically allocates enough memory to fit 'capacity' elements.
 * Return value:
 * on success - GDS_SUCCESS,
 * on failure - one of the generic error codes representing an invalid argument, or GDS_ARR_ERR_MALLOC_FAIL.
 * Function may fail if 'array' is NULL, 'capacity' == 0, 'element_size' == 0. */
gds_err gds_array_init(GDSArray* array, size_t capacity, size_t element_size);

// ---------------------------------------------------------------------------------------------------------------------

/* Dynamically allocates memory for GDSArray. Calls gds_array_init() to initialize the newly created array.
 * Return value:
 * on success - address of dynamically allocated GDSArray. 
 * on failure - NULL. The function can fail because: allocating memory for the new array failed, or because
 * gds_array_init() returned an error code. */
GDSArray* gds_array_create(size_t capacity, size_t element_size);

// ---------------------------------------------------------------------------------------------------------------------

/* Frees dynamically allocated memory for array. Sets values of array's fields to default values.
 * If array == NULL, the function performs no action. This doesn't free memory pointed to by 'array'. */
void gds_array_destruct(GDSArray* array);

// ---------------------------------------------------------------------------------------------------------------------

/* Calculates address of element with index specified by 'pos'.
 * Return value:
 * on success: address of element with index specified by 'pos',
 * on failure: NULL. Function may fail if 'pos' is invalid/out of bounds or if array is NULL. */
void* gds_array_at(const GDSArray* array, size_t pos);

// ---------------------------------------------------------------------------------------------------------------------

/* Copies memory content pointed to by data into the array at 'pos'.
 * Function relies on gds_array_at() to find the required address for the following memcpy() call.
 * Return value:
 * on success - GDS_SUCCESS,
 * on failure - one of the generic error codes representing an invalid argument.
 * Function may fail if 'array' or 'data' are NULL or 'pos' is out of bounds('pos' >= array's count). */
gds_err gds_array_assign(GDSArray* array, const void* data, size_t pos);

// ---------------------------------------------------------------------------------------------------------------------

/* Swaps the data of elements at pos1 and pos2. If 'pos1' == 'pos2', the function performs no action.
 * on success - GDS_SUCCESS,
 * on failure - one of the generic error codes representing an invalid argument.
 * Function may fail if 'array or 'swap_buff'' are NULL or 'pos1' or 'pos2' 
 * are out of bounds('pos' >= array's count). */
gds_err gds_array_swap(GDSArray* array, size_t pos1, size_t pos2, void* swap_buff);

// ---------------------------------------------------------------------------------------------------------------------

/* Appends data pointed to by 'data' to the end of the array. Performs the call: 
 * gds_array_insert_at(array, data, array->count). The function will not be able to append the new element if
 * the array is at its capacity. In this case, it returns an appropriate error code.
 * Return value:
 * on success - GDS_SUCCESS,
 * on failure - one of the generic error codes representing an invalid argument or GDS_ARR_ERR_INSUFF_CAPACITY.
 * Function may fail if 'array' or 'data' are NULL. */
gds_err gds_array_push_back(GDSArray* array, const void* data);

// ---------------------------------------------------------------------------------------------------------------------

/* Inserts data pointed to by 'data' to index pos in the array. This is done by shifting all elements with
 * index greater or equal than 'pos' rightward(through a memmove() call), and inserting the element at the empty spot.
 * If pos == array's count, no shifting is performed. This function only works if the array is not at its capacity,
 * otherwise it returns an error code.
 * Return value:
 * on success - GDS_SUCCESS,
 * on failure - one of the generic error codes representing an invalid argument or GDS__ARR_ERR_INSUFF_CAPACITY.
 * Function may fail if 'array' or 'data' are NULL or 'pos' is out of bounds('pos' >= array's count). */
gds_err gds_array_insert_at(GDSArray* array, const void* data, size_t pos);

// ---------------------------------------------------------------------------------------------------------------------

/* Removes element with position 'pos' from array. This is done by shifting all elements with index greater than 'pos'
 * leftwards through a memmove() call.
 * This function will invoke array->_on_element_removal_func for the removed element.
 * Return value:
 * on success - GDS_SUCCESS,
 * on failure - one of the generic error codes representing an invalid argument. 
 * Function may fail if 'array' is NULL or 'pos' is out of bounds('pos' >= array's count).
 * If the array is empty, the function treats 'pos' as an invalid argument and returns the appropriate code. */
gds_err gds_array_remove_at(GDSArray* array, size_t pos);

// ---------------------------------------------------------------------------------------------------------------------

/* Removes last element in array by performing a call: gds_array_remove_at(array, array->count - 1);
 * Return value:
 * on success - GDS_SUCCESS,
 * on failure - one of the generic error codes representing an invalid argument('array' is NULL) or 
 * GDS_ARR_ERR_ARR_EMPTY(indicating the array is already empty). */
gds_err gds_array_pop_back(GDSArray* array);

// ---------------------------------------------------------------------------------------------------------------------

/* Empties the array. If the array is already empty, the function performs no work and returns GDS_SUCCESS.
 * Return value:
 * on success: GDS_SUCCESS,
 * on failure: one of the generic error codes representing an invalid argument('array' is NULL). */
gds_err gds_array_empty(GDSArray* array);

// ---------------------------------------------------------------------------------------------------------------------

/* Performs a realloc() on array's data, so the new data can fit 'capacity' elements. If 'capacity' == array's current
 * capacity, the function returns immediately. 
 * Verbose explanation:
 * 1. If array's count > 'capacity', the array will shrink.
 * 2. A realloc() call will be performed. If the call succeeds, array's data will point to the new location.
 * If the call fails, array's data will point to the old location. If shrinking of the array occurred AND the realloc()
 * call failed, the array will remain shrunk.
 * Return value:
 * on success - GDS_SUCCESS,
 * on failure - one of gds generic error codes or GDS_ARR_ERR_REALLOC_FAIL.
 * Function may fail if 'array' is NULL or 'capacity' == 0.*/
gds_err gds_array_realloc(GDSArray* array, size_t capacity);

// ---------------------------------------------------------------------------------------------------------------------

ssize_t gds_array_find(GDSArray* array, const void* data, bool (*compare_func)(const void*, const void*));

// ---------------------------------------------------------------------------------------------------------------------

/* Gets current count of elements in array. Assumes non-NULL argument. */
size_t gds_array_get_count(const GDSArray* array);

// ---------------------------------------------------------------------------------------------------------------------

/* Gets capacity of array. Assumes non-NULL argument. */
size_t gds_array_get_capacity(const GDSArray* array);

// ---------------------------------------------------------------------------------------------------------------------

/* Checks if the array is empty. Assumes non-NULL argument. */
bool gds_array_is_empty(const GDSArray* array);

// ---------------------------------------------------------------------------------------------------------------------

/* Returns element size of array. Assumes non-NULL argument. */
size_t gds_array_get_element_size(const GDSArray* array);

// ---------------------------------------------------------------------------------------------------------------------

/* Performs sizeof(GDSArray) and returns the value. */
size_t gds_array_get_struct_size();

// ------------------------------------------------------------------------------------------------------------------------------------------

#endif
