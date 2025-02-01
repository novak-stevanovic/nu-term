#include <stdlib.h>
#include <assert.h>

#include "nt_shared/nt_content_matrix.h"
#include "api/nt_vec_api.h"
#include "nt_shared/nt_display_cell.h"

// ----------------------------------------------------------------------------------------------------------------------

void _row_destruct(void* row_vec_ptr);
struct Vector* _vec_ptr_buff;
struct NTDisplayCell _element_buff;

// ----------------------------------------------------------------------------------------------------------------------

void nt_content_matrix_init(struct NTContentMatrix* content_matrix, size_t min_count_in_row,
        size_t resize_count_in_row, size_t rows_min_count, size_t rows_resize_count)
{
    assert(content_matrix != NULL);

    content_matrix->_min_element_count_in_row = min_count_in_row;
    content_matrix->_resize_count_in_row = resize_count_in_row;

    content_matrix->_rows = nt_vec_api_vec_create(rows_min_count, rows_resize_count, sizeof(void*), _row_destruct);
    assert(content_matrix->_rows != NULL);
}

void _row_destruct(void* row_vec_ptr)
{
    assert(row_vec_ptr != NULL);

    struct Vector** _row_vec_ptr = (struct Vector**)row_vec_ptr;
    assert(*_row_vec_ptr != NULL);

    nt_vec_api_vec_destuct(*_row_vec_ptr);
}


struct NTDisplayCell* nt_content_matrix_at(struct NTContentMatrix* content_matrix, size_t x, size_t y)
{
    assert(content_matrix != NULL);

    struct Vector** row_vec_ptr = (struct Vector**)nt_vec_api_vec_at(content_matrix->_rows, y);
    assert(row_vec_ptr != NULL);
    assert(*row_vec_ptr != NULL);

    return (struct NTDisplayCell*)nt_vec_api_vec_at(*row_vec_ptr, x);
}

void nt_content_matrix_set_size(struct NTContentMatrix* content_matrix, size_t height, size_t width)
{
    assert(content_matrix != NULL);
    if(height != 0) assert(width != 0);
    if(width != 0) assert(height != 0);

    struct Vector* rows = content_matrix->_rows;
    nt_vec_api_vec_set_size_gen(rows, height, _nt_content_matrix_row_gen_func, content_matrix);

    ssize_t row_count = nt_vec_api_vec_get_count(rows);
    assert(row_count != -1);

    int i;
    struct Vector** curr_row_vec_ptr;
    for(i = 0; i < row_count; i++)
    {
        curr_row_vec_ptr = nt_vec_api_vec_at(rows, i);
        assert(curr_row_vec_ptr != NULL);
        assert(*curr_row_vec_ptr != NULL);
        nt_vec_api_vec_set_size_gen(*curr_row_vec_ptr, width, _nt_content_matrix_element_gen_func, NULL);
    }

}

void* _nt_content_matrix_row_gen_func(void* data)
{
    assert(data != NULL);

    struct NTContentMatrix* _data = (struct NTContentMatrix*)data;

    struct Vector* new_row = nt_vec_api_vec_create(_data->_min_element_count_in_row,
            _data->_resize_count_in_row,
            sizeof(struct NTDisplayCell), NULL);

    _vec_ptr_buff = new_row;

    return &_vec_ptr_buff;
}

void* _nt_content_matrix_element_gen_func(void* data)
{
    _element_buff.bg_color_code = -1;
    _element_buff.fg_color_code = -1;
    _element_buff.content = 0;
    return &(_element_buff);
}

size_t nt_content_matrix_get_height(struct NTContentMatrix* content_matrix)
{
    assert(content_matrix != NULL);

    return nt_vec_api_vec_get_count(content_matrix->_rows);
}

size_t nt_content_matrix_get_width(struct NTContentMatrix* content_matrix)
{
    assert(content_matrix != NULL);

    struct Vector** ptr_to_first_row_vec = (struct Vector**)nt_vec_api_vec_at(content_matrix->_rows, 0);

    assert(ptr_to_first_row_vec != NULL);
    assert(*ptr_to_first_row_vec != NULL);

    return nt_vec_api_vec_get_count(*ptr_to_first_row_vec);
}
