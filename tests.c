#include <stdio.h>
#include <unistd.h>
#include "api/nt_vec_api.h"
#include "nt_primitives/nt_erase_prims.h"
#include "nt_shared/nt_content_matrix.h"

#include "nuterm.h"

int main(int argc, char *argv[])
{
    nt_eprim_erase_screen();
    nt_init();
    char c;
    read(STDIN_FILENO, &c, 1);
}
