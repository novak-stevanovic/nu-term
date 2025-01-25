#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "lib/gds_vector.h"
#include "lib/gds_misc.h"

#define _VEC_INTERNAL_ERR_BASE (VEC_ERR_BASE + 500)

struct GDSVector
{
    size_t count;
    size_t alloced_count;
    size_t count_in_chunk;
    size_t element_size;
    size_t min_count;
    void* data;
};

// --------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------

#define _VEC_SHIFT_R_ERR_BASE (_VEC_INTERNAL_ERR_BASE + 10)
#define _VEC_SHIFT_R_ERR_VEC_NULL (_VEC_SHIFT_R_ERR_BASE + 1)
#define _VEC_SHIFT_R_ERR_START_IDX_OUT_OF_BOUNDS (_VEC_SHIFT_R_ERR_BASE + 2)
#define _VEC_SHIFT_R_ERR_INSUFF_SPACE (_VEC_SHIFT_R_ERR_BASE + 3) // Happens when vector->count == vector->alloced_count.
                                                                  // This means there is not enough memory alloced to shift any elements rightwards.
#define _VEC_SHIFT_R_ERR_INVALID_ADDR (_VEC_SHIFT_R_ERR_BASE + 4) // gds_vec_at() returned null.

/* Shift elements right of index(including) start_idx rightward by calling memmove(). This function cannot expand the vector if there is not enough memory allocated.
 * Make sure that vector->count < vector->alloced_count before calling.
 * Return value:
 * on success: 0
 * on failure: one of the error codes above. */
static int _gds_vec_shift_right(struct GDSVector* vector, size_t start_idx);

// --------------------------------------------------------------------------------------------------------------------------------------------

#define _VEC_SHIFT_L_ERR_BASE (_VEC_INTERNAL_ERR_BASE + 20)
#define _VEC_SHIFT_L_ERR_VEC_NULL (_VEC_SHIFT_L_ERR_BASE + 1)
#define _VEC_SHIFT_L_ERR_START_IDX_OUT_OF_BOUNDS (_VEC_SHIFT_L_ERR_BASE + 2)
#define _VEC_SHIFT_L_ERR_INVALID_ADDR (_VEC_SHIFT_L_ERR_BASE + 4) // gds_vec_at() returned null.

/* Shift elements right of index(including) start_idx leftward by calling memmove().
 * Return value:
 * on success: 0
 * on failure: one of the error codes above. */
static int _gds_vec_shift_left(struct GDSVector* vector, size_t start_idx);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Gets count of chunks for given count, min_count and count_in_chunk parameters. For example:
 * For a vector with: 624 elements, min_count = 20, count_in_chunk = 100, the return value will be equal to 7 because 7 chunks of
 * 100 elements are required to store the whole vector. For the same vector with 601 elements, 6 chunks would suffice(600 + 20 > 601).
 * This function can be considered static in the object-oriented sense, as it is not tied to a particular vector.
 * Return value: count of chunks needed to store vector with given parameters. */
static size_t _gds_vec_get_count_of_chunks(ssize_t count, ssize_t min_count, ssize_t count_in_chunk);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Checks if vector has allocated more/less memory for its data than it needs based on the vector's:
 * current count, alloced_count, count_in_chunk, min_count and new_count parameter, where: new_count is the new count of elements
 * It uses the out_chunks_required parameter as an extra return value.
 * Return value:
 * 1: vector resizing is needed - out_chunks_required will be set to the count of required chunks of memory needed to store vector->data.
 * 0: vector resizing is not needed - out_chunks_required = 0. */
static int _gds_vec_is_resizing_needed(struct GDSVector* vector, size_t new_count, size_t* out_chunks_required);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Resizes vector by reallocating vector->data for (chunks_required * count_in_chunk * element_size + min_count * element_size) bytes of memory. 
 * This is in order to store the min_count of elements + the chunks needed to store the extra elements. This function does not check whether reallocating should happen, nor does
 * it check if a malloc() has been called for vector->data(). Make sure that: reallocating even needs to happen via the func _gds_vec_is_resizing_needed() and make sure that
 * vector->data != NULL.
 * Return value:
 * on success: 0
 * on failure: 1 - realloc() failed. */
static int _gds_vec_resize(struct GDSVector* vector, size_t chunks_required);

// --------------------------------------------------------------------------------------------------------------------------------------------

/* Function that performs work that functions: 1. gds_vec_set_size_val(...) and gds_vec_set_size_func(...) share:
 * 1. The function checks if resizing is needed for parameter new_count and saves the chunk required value.
 * 2. The function performs resizing of the vector's data according to chunks_required count.
 * 3. Adjusts the vector's count. 
 * Return value:
 * on success: 0,
 * on failure: 
 * 1 - parameter vector is NULL,
 * 2 - resizing failed(call to _gds_vec_resize()) */
static int _gds_vec_set_size_shared(struct GDSVector* vector, size_t new_size);

// --------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------

struct GDSVector* gds_vec_create(size_t min_count, size_t count_in_chunk, size_t element_size)
{
    if((count_in_chunk == 0) || (element_size == 0) || (min_count == 0)) return NULL;

    struct GDSVector* vector = (struct GDSVector*)malloc(sizeof(struct GDSVector));

    if(vector == NULL) return NULL;

    vector->data = malloc(element_size * min_count);

    if(vector->data == NULL)
    {
        free(vector);
        return NULL;
    }

    vector->element_size = element_size;
    vector->count_in_chunk = count_in_chunk;
    vector->min_count = min_count;
    vector->count = 0;
    vector->alloced_count = min_count;

    return vector;
}

void gds_vec_destruct(struct GDSVector* vector)
{
    if(vector == NULL) return;

    free(vector->data);

    vector->count = 0;
    vector->alloced_count = 0;
    vector->element_size = 0;
    vector->min_count = 0;
    vector->count_in_chunk = 0;
    vector->data = NULL;
}

int gds_vec_assign(struct GDSVector* vector, const void* data, size_t pos)
{
    if(vector == NULL) return VEC_ASSIGN_ERR_NULL_VEC;
    if(data == NULL) return VEC_ASSIGN_ERR_POS_OUT_OF_BOUNDS;
    if(pos >= vector->count) return VEC_ASSIGN_ERR_POS_OUT_OF_BOUNDS;

    void* addr = gds_vec_at(vector, pos);
    if(addr == NULL) return VEC_ASSIGN_ERR_INVALID_ADDR_FOUND;

    memcpy(addr, data, vector->element_size);
    return 0;
}

int gds_vec_insert(struct GDSVector* vector, const void* data, size_t pos)
{
    if(vector == NULL) return VEC_INSERT_ERR_NULL_VEC;
    if(data == NULL) return VEC_INSERT_ERR_NULL_DATA;

    size_t vector_count = vector->count;
    if(pos > vector_count) return VEC_INSERT_ERR_POS_OUT_OF_BOUNDS;

    size_t chunks_required;
    if(_gds_vec_is_resizing_needed(vector, vector_count + 1, &chunks_required)) 
    {
        int resize_op_status = _gds_vec_resize(vector, chunks_required);
        if(resize_op_status != 0) return VEC_INSERT_ERR_RESIZE_OP_FAILED;
    }

    if(pos < vector->count)
        if(_gds_vec_shift_right(vector, pos) != 0) return VEC_INSERT_ERR_SHIFTING_OP_FAILED;
    
    vector->count++; // it is important to increase the count first, so that the gds_vec_assign() function will work.

    int assign_op_status = gds_vec_assign(vector, data, pos);
    if(assign_op_status != 0) 
    {
        vector->count--;
        return VEC_INSERT_ERR_ASSIGN_OP_FAILED;
    }

    return 0;

}

int gds_vec_append(struct GDSVector* vector, const void* data)
{
    int insert_op_status = gds_vec_insert(vector, data, vector->count);
    if(insert_op_status != 0)
        return (insert_op_status - VEC_INSERT_ERR_BASE + VEC_APPEND_ERR_BASE); // convert to append error code
    else
        return 0;
}

int gds_vec_remove(struct GDSVector* vector, size_t pos)
{
    if(vector == NULL) return VEC_REMOVE_ERR_NULL_VEC;
    if(pos >= vector->count) return VEC_REMOVE_ERR_POS_OUT_OF_BOUNDS;

    if(pos < (vector->count - 1))
    {
        int shift_op_status = _gds_vec_shift_left(vector, pos + 1);
        if(shift_op_status != 0) return VEC_REMOVE_ERR_SHIFTING_OP_FAILED;
    }

    vector->count--;

    size_t chunks_required;
    if(_gds_vec_is_resizing_needed(vector, vector->count -1, &chunks_required))
    {
        int resize_op_status = _gds_vec_resize(vector, chunks_required);
        if(resize_op_status != 0) return VEC_REMOVE_ERR_RESIZE_OP_FAILED;
    }

    return 0;
}

int gds_vec_pop(struct GDSVector* vector)
{
    if(vector == NULL) return VEC_POP_ERR_NULL_VEC;
    if(vector->count == 0) return VEC_POP_ERR_VEC_EMPTY;

    int remove_op_status = gds_vec_remove(vector, vector->count - 1);
    if(remove_op_status != 0)
        return remove_op_status - VEC_REMOVE_ERR_BASE + VEC_POP_ERR_BASE; // convert to pop error code
    else
        return 0;
}

static int _gds_vec_set_size_shared(struct GDSVector* vector, size_t new_size)
{
    if(vector == NULL) return 1;

    size_t chunks_required;
    int resize_needed = _gds_vec_is_resizing_needed(vector, new_size, &chunks_required);

    if(resize_needed)
    {
        int resize_status = _gds_vec_resize(vector, chunks_required);
        if(resize_status != 0)
            return 2;
    }

    vector->count = new_size;
    return 0;
}

int gds_vec_set_size_val(struct GDSVector* vector, size_t new_size, void* default_val)
{
    if(vector == NULL) return VEC_SET_SIZE_VAL_NULL_VEC;

    size_t old_size = vector->count;

    int set_size_status = _gds_vec_set_size_shared(vector, new_size);
    if(set_size_status != 0) return VEC_SET_SIZE_VAL_SHARED_FAIL;

    if(old_size > new_size)
    {
        if(default_val == NULL) return VEC_SET_SIZE_VAL_NULL_DEFAULT_VAL;

        int i;
        int assign_status;
        for(i = old_size; i < new_size; i++)
        {
            assign_status = gds_vec_assign(vector, default_val, i);
            if(assign_status != 0) return VEC_SET_SIZE_VAL_ASSIGN_FAIL;
        }
    }

    return 0;
}

int gds_vec_set_size_gen(struct GDSVector* vector, size_t new_size, void* (*el_gen_func)(void* data), void* data)
{
    if(vector == NULL) return VEC_SET_SIZE_GEN_NULL_VEC;

    size_t old_size = vector->count;

    int set_size_status = _gds_vec_set_size_shared(vector, new_size);
    if(set_size_status != 0) return VEC_SET_SIZE_GEN_NULL_VEC;

    if(old_size > new_size)
    {
        if(el_gen_func == NULL) return VEC_SET_SIZE_GEN_NULL_GEN_FUNC;

        int i;
        int assign_status;
        for(i = old_size; i < new_size; i++)
        {
            assign_status = gds_vec_assign(vector, el_gen_func(data), i);
            if(assign_status != 0) return VEC_SET_SIZE_GEN_ASSIGN_FAIL;
        }
    }

    return 0;
}

int gds_vec_empty(struct GDSVector* vector)
{
    if(vector == NULL) return 1;

    int resize_status =_gds_vec_resize(vector, 0);
    if(resize_status != 0) return 2;

    vector->count = 0;
    return 0;

}

void* gds_vec_at(const struct GDSVector* vector, size_t pos)
{
    if(vector == NULL) return NULL;
    if(pos >= vector->count) return NULL;

    return vector->data + (pos * vector->element_size);
}

ssize_t gds_vec_get_count(const struct GDSVector* vector)
{
    if(vector == NULL) return -1;
    return vector->count;
}

ssize_t gds_vec_get_resize_count(const struct GDSVector* vector)
{
    if(vector == NULL) return -1;

    return vector->count_in_chunk;
}

int gds_vec_set_resize_count(struct GDSVector* vector, size_t count_in_chunk)
{
    if(vector == NULL) return -1;

    vector->count_in_chunk = count_in_chunk;
    return 0;
}

void* gds_vec_get_data(const struct GDSVector* vector)
{
    if(vector == NULL) return NULL;

    return vector->data;
}

size_t gds_vec_get_struct_size()
{
    return sizeof(struct GDSVector);
}

// --------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------

static int _gds_vec_shift_right(struct GDSVector* vector, size_t start_idx)
{
    if(vector == NULL) return _VEC_SHIFT_R_ERR_VEC_NULL;
    if(start_idx >= vector->count) return _VEC_SHIFT_R_ERR_START_IDX_OUT_OF_BOUNDS;

    size_t vector_count = vector->count;

    if(vector_count >= vector->alloced_count) return _VEC_SHIFT_R_ERR_INSUFF_SPACE;

    size_t step = vector->element_size;
    size_t elements_shifted = vector_count - start_idx;

    void* start_pos = gds_vec_at(vector, start_idx);
    if(start_pos == NULL) return _VEC_SHIFT_R_ERR_INVALID_ADDR;

    memmove(start_pos + step, start_pos, step * elements_shifted);

    return 0;
}

static int _gds_vec_shift_left(struct GDSVector* vector, size_t start_idx)
{
    if(vector == NULL) return _VEC_SHIFT_L_ERR_VEC_NULL;

    size_t vector_count = vector->count;

    if(start_idx >= vector->count) return _VEC_SHIFT_L_ERR_START_IDX_OUT_OF_BOUNDS;

    size_t step = vector->element_size;
    size_t elements_shifted = vector_count - start_idx;

    void* start_pos = gds_vec_at(vector, start_idx) - step;
    if(start_pos == NULL) return _VEC_SHIFT_L_ERR_INVALID_ADDR;

    memmove(start_pos, start_pos + step, step * elements_shifted);
    return 0;
}

static size_t _gds_vec_get_count_of_chunks(ssize_t count, ssize_t min_count, ssize_t count_in_chunk)
{
    return gds_misc_max(0, (count - min_count) / count_in_chunk + ((count - min_count) % count_in_chunk > 0));
}

static int _gds_vec_is_resizing_needed(struct GDSVector* vector, size_t new_count, size_t* out_chunks_required)
{
    ssize_t alloced_count = vector->alloced_count;
    ssize_t count_in_chunk = vector->count_in_chunk;
    ssize_t min_count = vector->min_count;

    ssize_t chunks_required = _gds_vec_get_count_of_chunks(new_count, min_count, count_in_chunk);
    ssize_t chunks_alloced = _gds_vec_get_count_of_chunks(alloced_count, min_count, count_in_chunk);

    if(chunks_required != chunks_alloced)
    {
        *out_chunks_required = chunks_required;
        return 1;
    }
    else
    {
        *out_chunks_required = 0;
        return 0;
    }
}

static int _gds_vec_resize(struct GDSVector* vector, size_t chunks_required)
{
    ssize_t count_in_chunk = vector->count_in_chunk;
    ssize_t element_size = vector->element_size;
    ssize_t min_count = vector->min_count;

    vector->data = realloc(vector->data, min_count * element_size + chunks_required * count_in_chunk * element_size);
    if(vector->data == NULL) return 1;
    vector->alloced_count = min_count + chunks_required * count_in_chunk;

    return 0;
}
