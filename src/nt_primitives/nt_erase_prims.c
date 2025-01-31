#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

#include "nt_primitives/nt_erase_prims.h"
#include "nt_primitives/nt_primitives.h"

void nt_eprim_erase_screen()
{
    snprintf(code_buff, CODE_BUFF_LEN, NT_EPRIM_ERASE_ENTIRE_SCREEN_CODE);
    WRITE_CODE;
}

void nt_eprim_erase_line()
{
    snprintf(code_buff, CODE_BUFF_LEN, NT_EPRIM_ERASE_ENTIRE_LINE_CODE);
    WRITE_CODE;
}

void nt_eprim_erase_line_start_to_cursor()
{
    snprintf(code_buff, CODE_BUFF_LEN, NT_EPRIM_ERASE_START_TO_CURSOR_LINE_CODE);
    WRITE_CODE;
}

void nt_eprim_erase_line_cursor_to_end()
{
    snprintf(code_buff, CODE_BUFF_LEN, NT_EPRIM_ERASE_CURSOR_TO_END_LINE_CODE);
    WRITE_CODE;
}
