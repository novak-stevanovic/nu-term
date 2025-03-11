#ifndef _NT_SOLID_COLOR_BLOCK_H_
#define _NT_SOLID_COLOR_BLOCK_H_

#include "nt_component/base/nt_simple_pane.h"
#include "nt_env/base/nt_gfx.h"

typedef struct NTSolidColorBlock
{
    NTSimplePane _base;
    NTColor _bg_color;
} NTSolidColorBlock;

void nt_solid_color_block_init(NTSolidColorBlock* solid_color_block,
        NTColor bg_color);

#endif // _NT_SOLID_COLOR_BLOCK_H_
