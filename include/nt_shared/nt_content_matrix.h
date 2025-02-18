#ifndef NT_CONTENT_MATRIX_H
#define NT_CONTENT_MATRIX_H

#include "gds_vector.h"

#include <stddef.h>

struct NTContentMatrix
{
    GDSVector _rows;
};

void nt_content_matrix_init(struct NTContentMatrix* content_matrix);

void nt_content_matrix_set_height(struct NTContentMatrix* content_matrix, size_t new_height);

void nt_content_matrix_set_width(struct NTContentMatrix* content_matrix, size_t new_width);

void nt_content_matrix_set_size(struct NTContentMatrix* content_matrix, size_t new_width, size_t new_height);

struct NTDisplayCell* nt_content_matrix_at(struct NTContentMatrix* content_matrix, size_t x, size_t y);

size_t nt_content_matrix_get_height(const struct NTContentMatrix* content_matrix);

size_t nt_content_matrix_get_width(const struct NTContentMatrix* content_matrix);

#endif
