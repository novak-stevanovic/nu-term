#include <stdio.h>
#include "nt_shared/nt_content_matrix.h"

int main(int argc, char *argv[])
{
    struct NTContentMatrix m;
    nt_content_matrix_init(&m, 10, 10, 10, 10);

    // printf("%ld %ld\n", nt_content_matrix_get_height(&m), nt_content_matrix_get_width(&m));

    nt_content_matrix_set_size(&m, 100, 50);

    printf("%ld %ld\n", nt_content_matrix_get_height(&m), nt_content_matrix_get_width(&m));

    nt_content_matrix_set_size(&m, 1, 1);

    printf("%ld %ld\n", nt_content_matrix_get_height(&m), nt_content_matrix_get_width(&m));

}
