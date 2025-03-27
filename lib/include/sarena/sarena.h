#ifndef _SARENA_H_
#define _SARENA_H_

#include <stdlib.h>

/* -------------------------------------------------------------------------- */

/* SArena is a simple thread-safe arena allocator. It contains regions organized
 * into a region list. When the tail of the region list runs out of memory in
 * its internal memory pool, a new region is pushed back to the list.
 *
 * The SArena may also be rewinded, which will empty all of the allocated
 * regions (and their internal memory pools), allowing the user to
 * re-populate the once-used memory pools.
 *
 * This arena may perform poorly if 'region_cap' is too small relative to the
 * typical allocation size.
 *
 * It is important to note that each SArena object has its own lock,
 * assuring optimal performance in a multi-threaded environment. Thread-safety
 * is achieved using pthreads. */

struct SArena;
typedef struct SArena SArena;

typedef int sa_err;

#define SA_SUCCESS 0
#define SA_MALLOC_FAIL 2410
#define SA_INVALID_ARG 2411

/* -------------------------------------------------------------------------- */

/* Dynamically allocates memory for 'struct SArena' and initializes it. 
 * Dynamically allocates memory for the first memory region, initializes it
 * (which also means that it dynamically allocates memory for its memory pool)
 * and pushes it back to the region list.
 *
 * Each region inside the arena will be capable of holding at most
 * 'region_cap' bytes of data.
 *
 * Using an arena before initializing it is undefined behavior.
 *
 * Possible errors:
 * 1. SA_MALLOC_FAIL - if malloc() fails;
 * 2. SA_INVALID_ARG - if 'region_cap' is 0. 
 *
 * Return value:
 * ON SUCCESS: address of the newly-allocated SArena;
 * ON FAILURE: NULL. */

SArena* sarena_create(size_t region_cap, sa_err* out_err);

/* -------------------------------------------------------------------------- */

/* Destroys the arena. This will destroy every region inside the region list.
 * 'Destroying a region implies freeing the memory occupied by the region's
 * memory pool. This also frees the dynamically allocated memory to
 * store the SArena object itself. */

void sarena_destroy(SArena* arena);

/* -------------------------------------------------------------------------- */

/* This function allocates memory within the arena. It finds the currently active
 * region in the list and attempts to allocate the requested memory size within
 * its internal memory pool. 'Currently active region' refers to:
 *
 * 1) If 'rewind mode' is off, the tail of the region list.
 * If that region does not have enough space, a new region may be created and
 * appended to the end of the list.
 *
 * 2) If 'rewind mode' is on, the first region containing free space inside its
 * memory pool. If that region does not have enough space, the next region will
 * be considered. 
 *
 * Possible errors:
 * 1. SA_MALLOC_FAIL - if malloc() fails;
 * 2. SA_INVALID_ARG - if 'size' is 0 or greater than arena's 'region_cap'.
 *
 * Calling sarena_destroy multiple times on a single SArena is undefined
 * behavior.
 *
 * Return value:
 * ON SUCCESS: address of the newly-allocated memory inside the arena
 * of 'size' bytes;
 * ON FAILURE: NULL. */

void* sarena_malloc(SArena* arena, size_t size, sa_err* out_err);

/* -------------------------------------------------------------------------- */

/* This function allocates a zero-initialized memory block of the given size 
 * from the SArena. It behaves similarly to sarena_malloc,
 * but ensures that the allocated memory is filled with zeros.

The return value and possible errors are the same as those for sarena_malloc. */

void* sarena_calloc(SArena* arena, size_t size, sa_err* out_err);

/* -------------------------------------------------------------------------- */

/* This function resets the arena by marking all allocated memory within
 * existing regions as available for reuse. It does not free any memory
 * but instead sets all regions' used capacity to zero. 
 * If multiple regions exist, the arena enters 'rewind mode' allowing
 * previously allocated regions to be reused in order. */

void sarena_rewind(SArena* arena);

/* -------------------------------------------------------------------------- */

/* This function deallocates all allocated regions except the first one.
 * This means that all memory occupied by those regions will be freed.
 * The first region will be reset, making its memory available for reuse.
 * After this call, the arena will be in the same state as immediately
 * after sarena_init(). */

void sarena_reset(SArena* arena);

/* -------------------------------------------------------------------------- */

#endif // _SARENA_H_
