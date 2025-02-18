#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "nt_shared/nt_content_matrix.h"
#include "nt_core/nt_color.h"
#include "nt_shared/nt_display_cell.h"

// ----------------------------------------------------------------------------------------------------------------------

void _row_destruct(void* row_vec_ptr);

// ----------------------------------------------------------------------------------------------------------------------

void nt_content_matrix_init(struct NTContentMatrix* content_matrix)
{
    assert(content_matrix != NULL);

    gds_vector_init_default(&content_matrix->_rows, sizeof(GDSVector*));
}

void nt_content_matrix_set_height(struct NTContentMatrix* content_matrix, size_t new_height)
{
    assert(content_matrix != NULL);

    size_t height = nt_content_matrix_get_height(content_matrix);
    size_t width = nt_content_matrix_get_width(content_matrix);
    GDSVector* rows = &content_matrix->_rows;

    size_t i, j;
    GDSVector* curr_new_row = NULL;
    struct NTDisplayCell display_cell_bp;
    nt_display_cell_init(&display_cell_bp, 1, 1, 0);

    for(i = height; i < new_height; i++)
    {
        curr_new_row = gds_vector_create_default(sizeof(struct NTDisplayCell));
        gds_vector_push_back(rows, &curr_new_row);
        
        for(j = 0; j < width; j++) gds_vector_push_back(curr_new_row, &display_cell_bp);
    }
}

void nt_content_matrix_set_width(struct NTContentMatrix* content_matrix, size_t new_width)
{
    assert(content_matrix != NULL);

    size_t height = nt_content_matrix_get_height(content_matrix);
    size_t width = nt_content_matrix_get_width(content_matrix);
    GDSVector* rows = &content_matrix->_rows;

    size_t i, j;
    GDSVector* curr_row = NULL;
    struct NTDisplayCell display_cell_bp;
    nt_display_cell_init(&display_cell_bp, 1, 1, 0);

    for(i = 0; i < height; i++)
    {
        curr_row = gds_vector_at(rows, i);

        for(j = width; j < new_width; j++) gds_vector_push_back(curr_row, &display_cell_bp);
    }
}

void nt_content_matrix_set_size(struct NTContentMatrix* content_matrix, size_t new_width, size_t new_height)
{
    nt_content_matrix_set_height(content_matrix, new_height);
    nt_content_matrix_set_width(content_matrix, new_width);
}

struct NTDisplayCell* nt_content_matrix_at(struct NTContentMatrix* content_matrix, size_t x, size_t y)
{
    size_t height = nt_content_matrix_get_height(content_matrix);
    size_t width = nt_content_matrix_get_width(content_matrix);

    assert(x < width);
    assert(y < height);

    GDSVector* row = *(GDSVector**)gds_vector_at(&content_matrix->_rows, y);

    return gds_vector_at(row, x);
}

size_t nt_content_matrix_get_height(const struct NTContentMatrix* content_matrix)
{
    assert(content_matrix != NULL);

    return gds_vector_get_count(&content_matrix->_rows);
}

size_t nt_content_matrix_get_width(const struct NTContentMatrix* content_matrix)
{
    assert(content_matrix != NULL);

    if(nt_content_matrix_get_height(content_matrix) == 0) return 0;

    GDSVector** ptr_to_first_row_vec = gds_vector_at(&content_matrix->_rows, 0);
    GDSVector* first_row_vec = *ptr_to_first_row_vec;

    if(first_row_vec == NULL) return 0;
    else return gds_vector_get_count(first_row_vec);
}


