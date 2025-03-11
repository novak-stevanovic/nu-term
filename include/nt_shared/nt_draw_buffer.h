#ifndef _NT_DRAW_BUFFER_H_
#define _NT_DRAW_BUFFER_H_

#include <stddef.h>

struct NTDisplayCell;
typedef struct NTDisplayCell NTDisplayCell;

typedef struct NTDrawBuffer
{
    NTDisplayCell** _buffer;
    size_t _width, _height;
} NTDrawBuffer;

void nt_draw_buffer_init(NTDrawBuffer* draw_buffer);

void nt_draw_buffer_set_size(NTDrawBuffer* draw_buffer, size_t width, size_t height);

#endif // _NT_DRAW_BUFFER_H_
