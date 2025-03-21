#include <signal.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <assert.h>

#include "nt_env/nt_display.h"
#include "nt_component/base/nt_pane.h"
#include "nt_core/nt_platform.h"
#include "nt_core/nt_platform_request.h"
#include "nt_env/nt_draw_engine.h"
#include "nt_env/base/nt_cursor.h"
#include "nt_env/nt_display_cell.h"
#include "nt_util/nt_log.h"

NTDisplayCell _display_buffer[NT_DISPLAY_MAX_HEIGHT][NT_DISPLAY_MAX_WIDTH];

static struct sigaction _old_sigact;
volatile static size_t _display_width, _display_height;

static NTObject* _root;

static void _update_display_size();
static void _sigwinch_sa_handler(int signum);

/* NT_PLATFORM -------------------------------------------------------------- */

static size_t _platform_slot_idx;

nt_platform struct _ChangeSizeData
{
    size_t new_width, new_height;
};

static nt_platform void __change_size_func(void* _req_data);

/* -------------------------------------------------------------------------- */

void _nt_display_init()
{
    _root = NULL;
    struct sigaction sa = {0};
    sa.sa_handler = &_sigwinch_sa_handler;

    sigaction(SIGWINCH, &sa, &_old_sigact);

    size_t i, j;
    for(i = 0; i < NT_DISPLAY_MAX_HEIGHT; i++)
    {
        for(j = 0; j < NT_DISPLAY_MAX_WIDTH; j++)
            nt_display_cell_init(&_display_buffer[i][j]);
    }

    _platform_slot_idx = nt_platform_designate_slot();

    _update_display_size();
}

void _nt_display_destroy()
{
    _display_width = 0;
    _display_height = 0;

    sigaction(SIGWINCH, &_old_sigact, NULL); // restore the old sigaction
}

static void inline _draw_cell_to_display_buffer(NTDrawCell draw_cell,
        size_t x, size_t y, NTPane* pane)
{
    nt_display_cell_update(&_display_buffer[y][x], draw_cell, pane);
}

void _nt_display_draw_pane_to_buffer(NTPane* pane)
{
    NTDrawBuffer* draw_buffer = nt_pane_get_draw_buffer(pane);

    const NTObject* pane_obj = (const NTObject*)pane;
    const NTBounds* content_bounds = nt_object_get_content_bounds(pane_obj);

    size_t width = nt_draw_buffer_get_width(draw_buffer);
    size_t height = nt_draw_buffer_get_height(draw_buffer);

    size_t start_x, start_y;
    nt_bounds_calculate_abs_coordinates(content_bounds,
            &start_x, &start_y, NULL, NULL);

    size_t i, j;
    NTDrawCell* curr_cell;
    for(i = 0; i < height; i++)
    {
        if(i > _display_height) nt_log("i > _display_height!!!!!!!!");
        for(j = 0; j < width; j++)
        {
            if(j > _display_width) nt_log("j: %ld _display_width: %ld", j, _display_width);
            curr_cell = NT_DRAW_BUFFER_GET_CELL_AT(draw_buffer, j, i);
            _draw_cell_to_display_buffer(*curr_cell, start_x + j, start_y + i, pane);
        }
    }
}

size_t nt_display_get_width()
{
    return _display_width;
}

size_t nt_display_get_height()
{
    return _display_height;
}

void nt_display_set_root(NTObject* object)
{
    _root = object;
    _update_display_size();
}

NTObject* nt_display_get_root()
{
    return _root;
}

/* -------------------------------------------------------------------------- */

static void _update_display_size()
{
    struct winsize win_size;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &win_size);

    struct _ChangeSizeData req_data;
    req_data.new_width = win_size.ws_col;
    req_data.new_height = win_size.ws_row;

    NTPlatformRequest req;
    nt_platform_request_init(&req,
            __change_size_func, &req_data, sizeof(struct _ChangeSizeData));

    nt_platform_write_to_slot(&req, _platform_slot_idx);
}

static void _sigwinch_sa_handler(int signum)
{
    _update_display_size();
}

void __change_size_func(void* _req_data)
{
    struct _ChangeSizeData* req_data =
        (struct _ChangeSizeData*)_req_data;

    _display_width = req_data->new_width;
    _display_height = req_data->new_height;

    // nt_log("NT_DISPLAY: Resize! Current size: %zu %zu.", _display_width, _display_height);
    if(_root != NULL)
    {
        NTBounds new_root_bounds;
        nt_bounds_init(&new_root_bounds, 0, 0,
                _display_width, _display_height, NULL);

        _nt_object_set_bounds(_root, &new_root_bounds);
        nt_draw_engine_draw_object_tree(_root);
    }
}

