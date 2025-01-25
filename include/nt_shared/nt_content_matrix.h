#ifndef NT_CONTENT_MATRIX_H
#define NT_CONTENT_MATRIX_H

#include <stddef.h>

#define NT_CONTENT_MATRIX_ROW_MIN_COUNT 10
#define NT_CONTENT_MATRIX_ROW_COUNT_IN_CHUNK 5

struct NTContentMatrix
{
    struct Vector* _rows;
    struct Vector* (*_row_gen_func)(void);
    struct TCDisplayCell* (*_element_gen_func)(void);
};

void nt_content_matrix_init(struct NTContentMatrix* content_matrix);

struct TCDisplayCell* nt_content_matrix_at(struct NTContentMatrix* content_matrix, size_t x, size_t y);

void nt_content_matrix_set_size(struct NTContentMatrix* content_matrix, size_t height, size_t width);

#endif
