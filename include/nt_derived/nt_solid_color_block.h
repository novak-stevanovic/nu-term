#ifndef NT_SOLID_COLOR_BLOCK_H
#define NT_SOLID_COLOR_BLOCK_H

#include "nt_base/nt_window.h"

typedef struct NTSolidColorBlock
{
    NTWindow _base;
    
    nt_color _color;
} NTSolidColorBlock;

void nt_solid_color_block_init(NTSolidColorBlock* solid_color_block, nt_color color);

nt_color nt_solid_color_block_get_color(const NTSolidColorBlock* solid_color_block);
void nt_solid_color_block_set_color(NTSolidColorBlock* solid_color_block, nt_color color_code);

#endif
