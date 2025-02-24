#ifndef NT_SOLID_COLOR_BLOCK_H
#define NT_SOLID_COLOR_BLOCK_H

#include "nt_base/nt_simple_window.h"

struct NTContainer;

struct NTSolidColorBlock
{
    struct NTSimpleWindow _base;
    size_t _color_code;
};

void nt_solid_color_block_init(struct NTSolidColorBlock* solid_color_block,
        size_t color_code, NTDrawEngineDrawPriority draw_priority);

size_t nt_solid_color_block_get_color(struct NTSolidColorBlock* solid_color_block);
void nt_solid_color_block_set_color(struct NTSolidColorBlock* solid_color_block, size_t color_code);

#endif

