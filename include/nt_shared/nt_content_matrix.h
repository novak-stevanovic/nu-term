#ifndef NT_CONTENT_MATRIX_H
#define NT_CONTENT_MATRIX_H

#include <stddef.h>

struct NTContentMatrix
{
    struct Vector* _rows;

    size_t _min_element_count_in_row;
    size_t _resize_count_in_row;
};

/* Initializes provided content_matrix. Other params:
 * 1. min_count_in_row - min_count of each row,
 * 2. resize_count_in_row - resize_count/count_in_chunk of each row,
 * 3. rows_min_count - min_count of _rows vector,
 * 4. rows_resize_count - resize_count/count_in_chunk of _rows vector. */
void nt_content_matrix_init(struct NTContentMatrix* content_matrix, size_t min_count_in_row,
        size_t resize_count_in_row, size_t rows_min_count, size_t rows_resize_count);

struct TCDisplayCell* nt_content_matrix_at(struct NTContentMatrix* content_matrix, size_t x, size_t y);

void nt_content_matrix_set_size(struct NTContentMatrix* content_matrix, size_t height, size_t width);

void* _nt_content_matrix_row_gen_func(void* data);
void* _nt_content_matrix_element_gen_func(void* data);

#endif
