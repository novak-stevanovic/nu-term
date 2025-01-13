#ifndef NT_DYNAMIC_MATRIX_H
#define NT_DYNAMIC_MATRIX_H

#include <stddef.h>

struct NTDynamicMatrix
{
    struct Vector* _rows; 
    struct Vector* (*_gen_row_func)(void);
    struct Vector* (*_gen_element_func)(void);
};

void nt_dyn_matrix_init(struct NTDynamicMatrix* dyn_matrix,
        struct Vector* (*gen_row_func)(void),
        struct Vector* (*gen_element_func)(void),
        size_t row_min_count,
        size_t row_chunk_count);

void nt_dyn_matrix_set_size(struct NTDynamicMatrix* dyn_matrix, size_t height, size_t width);

void* nt_dyn_matrix_at(struct NTDynamicMatrix* dyn_matrix, size_t y, size_t x);

size_t nt_dyn_matrix_get_height(struct NTDynamicMatrix* dyn_matrix);
size_t nt_dyn_matrix_get_width(struct NTDynamicMatrix* dyn_matrix);

#endif
