#include <stdio.h>
#include <unistd.h>
#include <assert.h>

#include "nt_primitives/nt_style_prims.h"
#include "nt_primitives/nt_primitives.h"

void nt_sprim_gfx_reset()
{
    snprintf(code_buff, CODE_BUFF_LEN, NT_SPRIM_GFX_RESET_CODE);
    WRITE_CODE;
}

void nt_sprim_set_style_mode(size_t set_style_code)
{
    snprintf(code_buff, CODE_BUFF_LEN, NT_SPRIM_SET_STYLE_MODE_CODE, set_style_code);
    WRITE_CODE;
}
void nt_sprim_reset_style_mode(size_t reset_style_code)
{
    snprintf(code_buff, CODE_BUFF_LEN, NT_SPRIM_RESET_STYLE_MODE_CODE, reset_style_code);
    WRITE_CODE;
}

void nt_sprim_set_fg_color_8(size_t color_code)
{
    assert(color_code < 8);
    snprintf(code_buff, CODE_BUFF_LEN, NT_SPRIM_SET_FG_COLOR_CODE_C8, color_code);
    WRITE_CODE;
}

void nt_sprim_set_bg_color_8(size_t color_code)
{
    assert(color_code < 8);
    snprintf(code_buff, CODE_BUFF_LEN, NT_SPRIM_SET_BG_COLOR_CODE_C8, color_code);
    WRITE_CODE;
}

void nt_sprim_set_fg_color_256(size_t color_code)
{
    assert(color_code < 256);
    snprintf(code_buff, CODE_BUFF_LEN, NT_SPRIM_SET_BG_COLOR_CODE_C256, color_code);
    WRITE_CODE;
}

void nt_sprim_set_bg_color_256(size_t color_code)
{
    assert(color_code < 256);
    snprintf(code_buff, CODE_BUFF_LEN, NT_SPRIM_SET_BG_COLOR_CODE_C256, color_code);
    WRITE_CODE;
}

// void nt_sprim_set_default_fg_color()
// {
//     snprintf(code_buff, CODE_BUFF_LEN, NT_SPRIM_SET_FG_COLOR_CODE_C8, _NT_SPRIM_SET_FG_DEFAULT_COLOR_CODE_VAL);
//     WRITE_CODE;
// }
//
// void nt_sprim_set_default_bg_color()
// {
//     snprintf(code_buff, CODE_BUFF_LEN, NT_SPRIM_SET_BG_COLOR_CODE_C8, _NT_SPRIM_SET_BG_DEFAULT_COLOR_CODE_VAL);
//     WRITE_CODE;
// }
