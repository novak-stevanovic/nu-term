#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <asm/termbits.h>
#include <sys/ioctl.h>
#include <assert.h>

#include "nt_core/nt_display.h"
#include "nt_base/nt_constraints.h"
#include "nt_base/nt_object.h"
#include "nt_core/nt_color.h"
#include "nt_core/nt_cursor.h"
#include "nt_core/nt_draw_engine.h"
#include "nt_core/nt_erase.h"

#define SIGWINCH 28

static void _update_display_size();
static void _sigwinch_sa_handler(int signum);

// ---------------------------------------------------------------------------------------------------------

ssize_t bg_color_code, fg_color_code;
size_t display_height, display_width;

struct NTObject* root;

void nt_display_init()
{
    // TODO --- ?? erase??
    nt_erase_erase_screen(NT_COLOR_DEFAULT);


    struct sigaction sa = {0};
    sa.sa_handler = &_sigwinch_sa_handler;

    int sigact_status = sigaction(SIGWINCH, &sa, NULL);
    assert(sigact_status == 0);

    _update_display_size();
    bg_color_code = NT_DISPLAY_DEFAULT_COLOR;
    fg_color_code = NT_DISPLAY_DEFAULT_COLOR;
    root = NULL;
}

void nt_display_draw_from_root()
{
    nt_erase_erase_screen(NT_DISPLAY_DEFAULT_COLOR);
    if(root == NULL) return;

    struct NTConstraints root_constraints;
    nt_constraints_init(&root_constraints, display_width, display_height, display_width, display_height);

    nt_object_draw((struct NTObject*)root, &root_constraints);

    _nt_object_set_object_position_based_on_dimensions(root, 0, 0, display_width, display_height);

    nt_draw_engine_draw();
}

void nt_display_set_root(struct NTObject* new_root)
{
    root = new_root;
    //TODO -- REDRAW?
}

struct NTObject* nt_display_get_root()
{
    return root;
}

void nt_display_set_bg_color(ssize_t color_code)
{
    bg_color_code = color_code;
}

void nt_display_set_fg_color(ssize_t color_code)
{
    fg_color_code = color_code;
}

ssize_t nt_display_get_bg_color()
{
    return bg_color_code;
}

ssize_t nt_display_get_fg_color()
{
    return fg_color_code;
}

size_t nt_display_get_display_width()
{
    return display_width;
}

size_t nt_display_get_display_height()
{
    return display_height;
}

static void _update_display_size()
{
    struct winsize win_size;
    int ioctl_status = ioctl(STDIN_FILENO, TIOCGWINSZ, &win_size);

    assert(ioctl_status == 0);

    display_height = win_size.ws_row;
    display_width = win_size.ws_col;

    nt_cursor_conform_pos_to_display();

    nt_display_draw_from_root();

    // printf("DDD: %ld %ld\n", display_width, display_height);
}

static void _sigwinch_sa_handler(int signum)
{
    _update_display_size();
}

int nt_display_is_in_bounds(size_t x, size_t y)
{
    return (x < display_width) && (y < display_height);
}
