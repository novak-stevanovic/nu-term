#include <stdio.h>
#include "api/nt_vec_api.h"
#include "nt_shared/nt_content_matrix.h"

int main(int argc, char *argv[])
{
    struct NTContentMatrix m[100];
    int i;
    for(i = 0; i < 100; i++)
    {
        nt_content_matrix_init(&m[i], 10, 10, 10, 10);
    }
    printf("INITED\n");
    for(i = 0; i < 100; i++)
    {
        nt_content_matrix_set_size(&m[i], 200, 200);
    }
    printf("1\n");
    for(i = 0; i < 100; i++)
    {
        nt_content_matrix_set_size(&m[i], 200, 200);
    }
    printf("2\n");
    for(i = 0; i < 100; i++)
    {
        nt_content_matrix_set_size(&m[i], 2, 2);
    }
    printf("3\n");
    for(i = 0; i < 100; i++)
    {
        printf("i %d\n", i);
        nt_content_matrix_set_size(&m[i], 2500, 2500);
    }
    printf("4\n");
    for(i = 0; i < 100; i++)
    {
        nt_vec_api_vec_destuct(m[i]._rows);
    }

}
