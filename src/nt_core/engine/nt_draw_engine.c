#include "nt_core/engine/nt_draw_engine.h"
#include "nt_component/base/nt_object.h"
#include "nt_core/platform/nt_platform.h"
#include "nt_core/platform/nt_platform_request.h"
#include "nt_env/nt_cursor.h"
#include "nt_core/display/nt_display.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

static void _nt_draw_engine_draw_display_buffer();

/* NT_PLATFORM -------------------------------------------------------------- */

struct __DrawObjTreeReqData
{
    NTObject* object;
    bool arrange_anchored;
};

nt_platform static void __draw_object_tree_func(void* _draw_obj_tree_req_data)
{
    struct __DrawObjTreeReqData* draw_obj_tree_req_data=
        (struct __DrawObjTreeReqData*)_draw_obj_tree_req_data;

    NTObject* object = draw_obj_tree_req_data->object;

    _nt_object_arrange(object, true);
    _nt_object_display(object);
    _nt_draw_engine_draw_display_buffer();
}

/* -------------------------------------------------------------------------- */

void _nt_draw_engine_init()
{
}

void _nt_draw_engine_destroy()
{
}

void nt_draw_engine_draw_object_tree(NTObject* object)
{
    struct __DrawObjTreeReqData data;
    data.object = object;
    data.arrange_anchored = true;

    NTPlatformRequest req;
    nt_platform_request_init(&req, __draw_object_tree_func,
            &data, sizeof(struct __DrawObjTreeReqData));

    nt_platform_execute(&req);
}

#define BUFF_SIZE 2000
static char _buffer[BUFF_SIZE];
#define ENABLE_BUFFERING() setvbuf(stdout, _buffer, _IOFBF, BUFF_SIZE)
#define DISABLE_BUFFERING() setvbuf(stdout, NULL, _IONBF, 0)
#define FLUSH() fflush(stdout);

static void _nt_draw_engine_draw_display_buffer()
{
    size_t width = nt_display_get_width();
    size_t height = nt_display_get_height();

    size_t i, j;

    NTDisplayCell* curr_display_cell;
    ENABLE_BUFFERING();
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            curr_display_cell = &_display_buffer[i][j];

            nt_style_set(curr_display_cell->_style);
            nt_color_set_fg(curr_display_cell->_fg_color);
            nt_color_set_bg(curr_display_cell->_bg_color);
            nt_cursor_abs_move_to_xy(j, i);
            putchar(curr_display_cell->_content);
        }
    }

    FLUSH();
    DISABLE_BUFFERING();
}
