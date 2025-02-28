#ifndef NT_WINDOW_H
#define NT_WINDOW_H

#include "nt_base/nt_object.h"
#include "nt_base/nt_display_cell.h"

struct GDSArray;
typedef struct GDSArray GDSArray;

enum NTWindowDrawPriority { NT_WINDOW_DRAW_PRIORITY_REGULAR, NT_WINDOW_DRAW_PRIORITY_BACKGROUND };
typedef enum NTWindowDrawPriority NTWindowDrawPriority;

typedef struct NTWindow
{
    NTObject _base;

    NTDisplayCell (*_window_get_content_at_func)(const struct NTWindow* window,
            size_t x, size_t y);

    NTWindowDrawPriority _draw_priority;
    
} NTWindow;

void nt_window_init(NTWindow* window, 

        void (*object_calculate_req_size_func)(const NTObject* window,
            size_t* out_width, size_t* out_height),

        void (*object_arrange_func)(NTObject* window),

    NTDisplayCell (*window_get_content_at_func)(const NTWindow* window,
            size_t x, size_t y));

NTDisplayCell nt_window_get_content_at(const NTWindow* window, size_t x, size_t y);

bool nt_window_has_draw_priority_background(const NTWindow* window);

void nt_window_change_draw_priority(NTWindow* window);

#endif // NT_WINDOW_H
