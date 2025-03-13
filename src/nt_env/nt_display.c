#include <signal.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "nt_env/nt_display.h"
#include "nt_component/base/nt_pane.h"
#include "nt_core/nt_draw_engine.h"
#include "nt_env/base/nt_cursor.h"
#include "nt_env/nt_display_cell.h"
#include "nt_util/nt_log.h"

NTDisplayCell _display_buffer[NT_DISPLAY_MAX_HEIGHT][NT_DISPLAY_MAX_WIDTH];

static struct sigaction _old_sigact;
static size_t _display_width, _display_height;

static NTObject* _root;

static void _update_display_size();
static void _sigwinch_sa_handler(int signum);
static void _resize_redraw_root();

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

    _update_display_size();
}

void _nt_display_destruct()
{
    _display_width = 0;
    _display_height = 0;

    sigaction(SIGWINCH, &_old_sigact, NULL); // restore the old sigaction
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
    _resize_redraw_root();
}

NTObject* nt_display_get_root()
{
    return _root;
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
        for(j = 0; j < width; j++)
        {
            curr_cell = NT_DRAW_BUFFER_GET_CELL_AT(draw_buffer, j, i);
            _draw_cell_to_display_buffer(*curr_cell, start_x + j, start_y + i, pane);
        }
    }
}

/* -------------------------------------------------------------------------- */

static void _update_display_size()
{
    struct winsize win_size;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &win_size);

    _display_height = win_size.ws_row;
    _display_width = win_size.ws_col;
}

static void _sigwinch_sa_handler(int signum)
{
    _update_display_size();
    nt_log("NT_DISPLAY: Resize! Current size: %zu %zu.", _display_width, _display_height);

    // nt_cursor_conform_pos_to_display();

    _resize_redraw_root();
}

static void _resize_redraw_root()
{
    if(_root != NULL)
    {
        NTBounds screen_bounds;
        nt_bounds_init(&screen_bounds, 0, 0, _display_width, _display_height, NULL);
        _nt_object_set_bounds(_root, &screen_bounds);

        nt_draw_engine_draw_object_tree(_root, true);
    }
}
