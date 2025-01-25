#include <assert.h>
#include <stdlib.h>

#include "nt_shared/nt_content_matrix.h"
#include "api/nt_vec_api.h"
#include "nt_shared/nt_display_cell.h"

void nt_content_matrix_init(struct NTContentMatrix* content_matrix, size_t min_count_in_row,
        size_t resize_count_in_row, size_t rows_min_count, size_t rows_resize_count)
{
    assert(content_matrix != NULL);

    content_matrix->_min_element_count_in_row = min_count_in_row;
    content_matrix->_resize_count_in_row = resize_count_in_row;

    content_matrix->_rows = nt_vec_api_vec_create(rows_min_count, rows_resize_count, sizeof(struct Vector*));
}

struct TCDisplayCell* nt_content_matrix_at(struct NTContentMatrix* content_matrix, size_t x, size_t y)
{
    assert(content_matrix != NULL);

    struct Vector* row = (struct Vector*)nt_vec_api_vec_at(content_matrix->_rows, y);
    assert(row != NULL);

    return (struct TCDisplayCell*)nt_vec_api_vec_at(row, x);
}

void nt_content_matrix_set_size(struct NTContentMatrix* content_matrix, size_t height, size_t width)
{
    // TODO - add freeing
    assert(content_matrix != NULL);

    struct Vector* rows = content_matrix->_rows;
    ssize_t row_count = nt_vec_api_vec_get_count(rows);
    assert(row_count != -1);

    int i;
    struct Vector* curr_row;
    for(i = 0; i < row_count; i++)
    {
        curr_row = nt_vec_api_vec_at(rows, i);
        nt_vec_api_vec_set_size_gen(curr_row, width, _nt_content_matrix_element_gen_func(NULL), NULL);
    }

    nt_vec_api_vec_set_size_gen(content_matrix->_rows, height, _nt_content_matrix_row_gen_func, content_matrix);

}

void* _nt_content_matrix_row_gen_func(void* data)
{
    assert(data != NULL);

    struct NTContentMatrix* _data = (struct NTContentMatrix*)data;

    return (void*)nt_vec_api_vec_create(_data->_min_element_count_in_row, _data->_resize_count_in_row, sizeof(struct Vector*));
}

void* _nt_content_matrix_element_gen_func(void* data)
{
    struct NTDisplayCell* new_element = (struct NTDisplayCell*)malloc(sizeof(struct NTDisplayCell));
    new_element->bg_color_code = -1;
    new_element->fg_color_code = -1;
    new_element->content = 0;
    return (void*)new_element;
}
