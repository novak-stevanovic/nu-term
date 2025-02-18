#ifndef _GDS_FORWARD_LIST_H_
#define _GDS_FORWARD_LIST_H_

#include <stdlib.h>
#include <stdbool.h>

#include "gds.h"

#ifdef GDS_ENABLE_OPAQUE_STRUCTS
struct GDSForwardList;
struct GDSForwardListIterator;
#else
#define __GDS_FORWARD_LIST_DEF_ALLOW__
#include "def/gds_forward_list_def.h"
#endif

typedef struct GDSForwardList GDSForwardList;
typedef struct GDSForwardListIterator GDSForwardListIterator;

// ------------------------------------------------------------------------------------------------------------------------------------------

#define GDS_FWDLIST_ERR_BASE 2100
#define GDS_FWDLIST_ERR_LIST_EMPTY 2101
#define GDS_FWDLIST_ERR_MALLOC_FAIL 2102

#define GDS_FWDLIST_ITER_ERR_OUT_OF_BOUNDS 2103

// ------------------------------------------------------------------------------------------------------------------------------------------

/* Initializes 'list' by setting values for its fields. This function is to be used only on uninitialized lists
 * (gds_forward_list_create initializes the list). It may also be used after gds_forward_list_destruct().
 * data_size must be greater than 0. _on_element_removal_func may be NULL.
 * Return value:
 * on success: GDS_SUCCESS,
 * on failure: one of the generic error codes representing invalid arguments or GDS_FWDLIST_ERR_MALLOC_FAIL. */
gds_err gds_forward_list_init(GDSForwardList* list, size_t data_size, void (*_on_element_removal_func)(void*));

// ---------------------------------------------------------------------------------------------------------------------

/* Dynamically allocates memory for a GDSForwardList. Performs a call to gds_forward_list_init() to initialize it.
 * Return value:
 * on success: address of newly allocated GDSForwardList,
 * on failure: NULL.
 * Function may fail if the memory allocation for the list failed, or if gds_forward_init() failed. */
GDSForwardList* gds_forward_list_create(size_t data_size, void (*_on_element_removal_func)(void*));

// ---------------------------------------------------------------------------------------------------------------------

/* Used as a destructor. Sets values of 'list' fields to default values.
 * Removes all elements from the list(invocations of list->_on_element_removal_func will be made).
 * If 'list' is NULL, function performs nothing. This doesn't free memory pointed to by 'list'. */
void gds_forward_list_destruct(GDSForwardList* list);

// ---------------------------------------------------------------------------------------------------------------------

/* Retrieves address of element with index 'pos' inside the list. This retrieves the data from the list directly
 * (not the internally used list nodes). If attempting to retrieve the list head or tail, the complexity will be O(1),
 * as both are stored inside the GDSForwardList structure. Otherwise, it's O(n).
 * Return value:
 * on success: address of element with index 'pos',
 * on failure: NULL. Function may fail if provided 'list' argument is NULL or if 'pos' is out of bounds. */
void* gds_forward_list_at(const GDSForwardList* list, size_t pos);

// ---------------------------------------------------------------------------------------------------------------------

/* Assigns data pointed to by 'data' to element with index 'pos' inside the list. This is done via memcpy().
 * Return value:
 * on success: GDS_SUCCESS,
 * on failure: one of the generic error codes representing invalid arguments.
 * Function may fail if 'list' or 'data' are NULL or if 'pos' is out of bounds. */ 
gds_err gds_forward_list_assign(GDSForwardList* list, const void* data, size_t pos);

// ---------------------------------------------------------------------------------------------------------------------

/* Functions swaps data of elements with indices 'pos1' and 'pos2'. Function performs no action if pos1 == pos2.
 * Make sure that swap_buff is of at least list->data_size size.
 * Return value:
 * on success: GDS_SUCCESS,
 * on failure: one of the generic error codes representing invalid arguments.
 * Function may fail if 'list' or 'swap_buff' are NULL or 'pos1' or 'pos2' are out of bounds. */
gds_err gds_forward_list_swap(GDSForwardList* list, size_t pos1, size_t pos2, void* swap_buff);

// ---------------------------------------------------------------------------------------------------------------------

/* Functions appends a new element at the end of a list in O(1) complexity. 
 * Return value:
 * on success: GDS_SUCCESS,
 * on failure: one of the generic error codes representing invalid arguments or GDS_FWDLIST_ERR_MALLOC_FAIL.
 * Function may fail if 'list' or 'data' are NULL, or if dynamic allocation of the new node fails. */
gds_err gds_forward_list_push_back(GDSForwardList* list, const void* data);

// ---------------------------------------------------------------------------------------------------------------------

/* Functions appends a new element at the start of a list in O(1) complexity. 
 * Return value:
 * on success: GDS_SUCCESS,
 * on failure: one of the generic error codes representing invalid arguments or GDS_FWDLIST_ERR_MALLOC_FAIL.
 * Function may fail if 'list' or 'data' are NULL, or if dynamic allocation of the new node fails. */
gds_err gds_forward_list_push_front(GDSForwardList* list, const void* data);

// ---------------------------------------------------------------------------------------------------------------------

/* Functions inserts a new element at index 'pos' in the array. If inserting at start or end, complexity will be
 * O(1). Otherwise, it's O(n).
 * Return value:
 * on success: GDS_SUCCESS,
 * on failure: one of the generic error codes representing invalid arguments or GDS_FWDLIST_ERR_MALLOC_FAIL.
 * Function may fail if 'list' or 'data' are NULL, or if dynamic allocation of the new node fails. The
 * function may also fail if 'pos' is out of bounds. */
gds_err gds_forward_list_insert_at(GDSForwardList* list, const void* data, size_t pos);

// ---------------------------------------------------------------------------------------------------------------------

/* Function removes an element from the start of the list. This is done in O(1) complexity.
 * This function will invoke list->_on_element_removal_func for the removed element, if non-NULL.
 * Return value:
 * on success: GDS_SUCCESS,
 * on failure: one of the generic error codes representing invalid arguments(if 'list' is NULL)
 * or GDS_FWDLIST_ERR_LIST_EMPTY. */
gds_err gds_forward_list_pop_front(GDSForwardList* list);

// ---------------------------------------------------------------------------------------------------------------------

/* Function removes an element with index 'pos' from the list.
 * This is done in O(1) complexity if removing the head. Otherwise, O(n).
 * This function will invoke list->_on_element_removal_func for the removed element, if non-NULL.
 * Return value:
 * on success: GDS_SUCCESS,
 * on failure: one of the generic error codes representing invalid arguments(if 'list' is NULL).
 * If the list is empty, 'pos' will be treated as an invalid argument and the function will return the error code
 * indicating that.*/
gds_err gds_forward_list_remove_at(GDSForwardList* list, size_t pos);

// ---------------------------------------------------------------------------------------------------------------------

/* Function empties the list. 
 * This function will invoke list->_on_element_removal_func for each removed element, if non-NULL. 
 * If the list is already empty, the function performs no action and returns GDS_SUCCESS.
 * Return value:
 * on success: GDS_SUCCESS,
 * on failure: one of the generic error codes representing invalid arguments(if 'list' is NULL). */
gds_err gds_forward_list_empty(GDSForwardList* list);

// ---------------------------------------------------------------------------------------------------------------------

/* Retrieves list->_data_size. This function assumes a non-NULL 'list' argument */
size_t gds_forward_list_get_data_size(const GDSForwardList* list);

// ---------------------------------------------------------------------------------------------------------------------

/* Retrieves list->_count. This function assumes a non-NULL 'list' argument */
size_t gds_forward_list_get_count(const GDSForwardList* list);

// ---------------------------------------------------------------------------------------------------------------------

/* Checks if the forward list is empty. This function assumes a non-NULL 'list' argument. */
bool gds_forward_list_is_empty(const GDSForwardList* list);

// ---------------------------------------------------------------------------------------------------------------------

/* Performs sizeof(GDSForwardList) and returns the value. */
size_t gds_forward_list_get_struct_size();

// ------------------------------------------------------------------------------------------------------------------------------------------

/* Initializes the GDSForwardList iterator. The iterator will point at the first element of the list.
 * Return value:
 * on success: GDS_SUCCESS,
 * on failure: one of the generic error codes representing invalid arguments(if 'list' or 'iterator' is NULL.)
 * or GDS_FWDLIST_ERR_LIST_EMPTY. */
gds_err gds_forward_list_iterator_init(GDSForwardList* list, GDSForwardListIterator* iterator);

// ---------------------------------------------------------------------------------------------------------------------

/* Dynamically allocates memory for the iterator and invokes gds_forward_list_iterator_init() to initialize it.
 * The caller is responsible for freeing the dynamically allocated memory for the GDSForwardListIterator after
 * using it.
 * Return value:
 * on success: address of the newly allocated GDSForwardListIterator,
 * on failure: NULL.
 * Function may fail if 'list' is NULL, allocation for GDSForwardListIterator fails, or if the call to
 * gds_forward_list_iterator_init() function fails. */
GDSForwardListIterator* gds_forward_list_iterator_create(GDSForwardList* list);

// ---------------------------------------------------------------------------------------------------------------------

/* Moves iterator to the next GDSForwardList node. 
 * Return value: 
 * on success: GDS_SUCCESS,
 * on failure: one of the generic error codes representing invalid arguments or GDS_FWDLIST_ITER_ERR_OUT_OF_BOUNDS.
 * Function may fail if 'iterator' is NULL or the iterator is at the end of the list.
 * Function may also return GDS_FAILURE if the program is an undefined state - if iterator is pointing at a NULL node. */
gds_err gds_forward_list_iterator_next(GDSForwardListIterator* iterator);

// ---------------------------------------------------------------------------------------------------------------------

/* Checks if the iterator has a next node to move to. The iterator doesn't have a next node when pointing to the end
 * of a list. Function assumes non-NULL 'iterator' */
bool gds_forward_list_iterator_has_next(GDSForwardListIterator* iterator);

// ---------------------------------------------------------------------------------------------------------------------

/* Retrieves the data of the GDSForwardList node the iterator is pointing at. Function assumes non-NULL 'iterator' */
void* gds_forward_list_iterator_get_data(GDSForwardListIterator* iterator);

// ------------------------------------------------------------------------------------------------------------------------------------------

/* Retrieves the position of the GDSForwardList node the iterator is pointing at. Function assumes non-NULL 'iterator' */
size_t gds_forward_list_iterator_get_pos(GDSForwardListIterator* iterator);

// ------------------------------------------------------------------------------------------------------------------------------------------

#endif
