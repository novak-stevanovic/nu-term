#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "api/nt_vec_api.h"
#include "nt_shared/nt_content_matrix.h"
#include "nt_core/nt_color.h"
#include "nt_shared/nt_display_cell.h"

// ----------------------------------------------------------------------------------------------------------------------

void _row_destruct(void* row_vec_ptr);

// ----------------------------------------------------------------------------------------------------------------------

void nt_content_matrix_init(struct NTContentMatrix* content_matrix, size_t min_count_in_row,
        size_t resize_count_in_row, size_t rows_min_count, size_t rows_resize_count)
{
    assert(content_matrix != NULL);

    content_matrix->_min_count_in_row = min_count_in_row;
    content_matrix->_resize_count_in_row = resize_count_in_row;

    content_matrix->_rows = nt_vector_create(rows_min_count, rows_resize_count, sizeof(NTVector*), _row_destruct);
    assert(content_matrix->_rows != NULL);
}

void _row_destruct(void* row_vec_ptr)
{
    // assert(row_vec_ptr != NULL);
    //
    // NTVector** _row_vec_ptr = (NTVector**)row_vec_ptr;
    // assert(*_row_vec_ptr != NULL);
    //
    // nt_vec_api_vec_destuct(*_row_vec_ptr);
}


struct NTDisplayCell* nt_content_matrix_at(struct NTContentMatrix* content_matrix, size_t x, size_t y)
{
    assert(content_matrix != NULL);

    NTVector** row_vec_ptr = (NTVector**)nt_vector_at(content_matrix->_rows, y);
    assert(row_vec_ptr != NULL);
    assert(*row_vec_ptr != NULL);

    return (struct NTDisplayCell*)nt_vector_at(*row_vec_ptr, x);
}

void _row_assign_func(void* ptr_to_ptr_to_vec, void* data)
{
    struct NTContentMatrix* _data = (struct NTContentMatrix*)data;

    NTVector* new_row = nt_vector_create(_data->_min_count_in_row, _data->_resize_count_in_row, sizeof(struct NTDisplayCell), _row_destruct);
    //
    // NTVector** _ptr = (NTVector**)ptr_to_ptr_to_vec;
    //
    // *_ptr = new_row;

    memcpy(ptr_to_ptr_to_vec, &new_row, sizeof(NTVector*));
}

void _element_assign_func(void* ptr_to_display_cell, void* data)
{
    struct NTDisplayCell* _ptr_to_display_cell = (struct NTDisplayCell*)ptr_to_display_cell;

    _ptr_to_display_cell->bg_color_code = NT_COLOR_DEFAULT;
    _ptr_to_display_cell->fg_color_code = NT_COLOR_DEFAULT;
    _ptr_to_display_cell->content = 'c';
    // _ptr_to_display_cell->bg_color_code = 1;
    // _ptr_to_display_cell->fg_color_code = 2;
    // _ptr_to_display_cell->content = 'c';
}

void nt_content_matrix_set_size(struct NTContentMatrix* content_matrix, size_t height, size_t width)
{
    // printf("SETTING SIZE TO: %d %d\n", height, width);
    assert(content_matrix != NULL);
    if(height != 0) assert(width != 0);
    if(width != 0) assert(height != 0);

    NTVector* rows = content_matrix->_rows;
    assert(nt_vector_set_size(rows, height, _row_assign_func, content_matrix) == 0);

    ssize_t row_count = nt_vector_get_count(rows);
    // printf("new row_count: %d\n", row_count);
    assert(row_count != -1);

    if(row_count == 0) return;

    int i;
    NTVector** curr_row_vec_ptr;
    for(i = 0; i < row_count; i++)
    {
        curr_row_vec_ptr = (NTVector**)nt_vector_at(rows, i);
        assert(curr_row_vec_ptr != NULL);
        assert(*curr_row_vec_ptr != NULL);
        assert(nt_vector_set_size(*curr_row_vec_ptr, width, _element_assign_func, content_matrix) == 0);
    }

}

size_t nt_content_matrix_get_height(struct NTContentMatrix* content_matrix)
{
    assert(content_matrix != NULL);

    return nt_vector_get_count(content_matrix->_rows);
}

size_t nt_content_matrix_get_width(struct NTContentMatrix* content_matrix)
{
    assert(content_matrix != NULL);

    NTVector** ptr_to_first_row_vec = (NTVector**)nt_vector_at(content_matrix->_rows, 0);

    if(ptr_to_first_row_vec == NULL) return 0;
    if(*ptr_to_first_row_vec == NULL) return 0;

    return nt_vector_get_count(*ptr_to_first_row_vec);
}
