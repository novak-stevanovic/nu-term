#include <assert.h>

#include "nt_misc/nt_dynamic_matrix.h"
#include "lib_incl/gends_vector.h"

struct Vector* vec_init(size_t, size_t, size_t);

void nt_dyn_matrix_init(struct NTDynamicMatrix* dyn_matrix,
        struct Vector* (*gen_row_func)(void),
        struct Vector* (*gen_element_func)(void),
        size_t row_min_count,
        size_t row_chunk_count)
{
    assert(dyn_matrix != NULL);

    dyn_matrix->_gen_row_func = gen_row_func;
    dyn_matrix->_gen_element_func = gen_element_func;

    dyn_matrix->_rows = vec_init(row_min_count, row_chunk_count, vec_get_struct_size());
}

void nt_dyn_matrix_set_size(struct NTDynamicMatrix* dyn_matrix, size_t height, size_t width)
{
    assert(dyn_matrix != NULL);
    assert(dyn_matrix->_rows != NULL);

    while(nt_dyn_matrix_get_height(dyn_matrix) < height)
        vec_append(dyn_matrix->_rows, dyn_matrix->_gen_row_func());

    while(nt_dyn_matrix_get_height(dyn_matrix) > height)
        vec_pop(dyn_matrix->_rows);
    
    int i;
    struct Vector* curr_row;
    for(i = 0; i < vec_get_count(dyn_matrix->_rows); i++)
    {
        curr_row = vec_at(dyn_matrix->_rows, i);
        vec_append(curr_row, dyn_matrix->_gen_element_func());

        while(vec_get_count(curr_row) < height)
            vec_append(curr_row, dyn_matrix->_gen_element_func());

        while(vec_get_count(curr_row) > height)
            vec_pop(curr_row);
    }
}

void* nt_dyn_matrix_at(struct NTDynamicMatrix* dyn_matrix, size_t y, size_t x)
{
    assert(dyn_matrix != NULL);
    assert(dyn_matrix->_rows != NULL);

    struct Vector* row = vec_at(dyn_matrix->_rows, y);

    assert(row != NULL);

    return vec_at(row, x);
}

size_t nt_dyn_matrix_get_height(struct NTDynamicMatrix* dyn_matrix)
{
    assert(dyn_matrix->_rows != NULL);
    return vec_get_count(dyn_matrix->_rows);
}

size_t nt_dyn_matrix_get_width(struct NTDynamicMatrix* dyn_matrix)
{
    assert(dyn_matrix != NULL);
    assert(dyn_matrix->_rows != NULL);
    assert(vec_get_count(dyn_matrix->_rows) > 0);

    struct Vector* row = vec_at(dyn_matrix->_rows, 0);
    return vec_get_count(row);
}
