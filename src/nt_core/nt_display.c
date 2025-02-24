#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <asm/termbits.h>
#include <sys/ioctl.h>

#include "nt_core/nt_display.h"
#include "nt_base/nt_constraints.h"
#include "nt_base/nt_object.h"
#include "nt_core/nt_color.h"
#include "nt_core/nt_cursor.h"
#include "nt_core/nt_draw_engine.h"
#include "nt_core/nt_erase.h"
#include "nt_shared/nt_display_cell.h"

#define SIGWINCH 28

static void _update_display_size();
static void _sigwinch_sa_handler(int signum);

// ---------------------------------------------------------------------------------------------------------

size_t display_height, display_width;

struct NTObject* root;

void nt_display_init()
{
    struct sigaction sa = {0};
    sa.sa_handler = &_sigwinch_sa_handler;

    sigaction(SIGWINCH, &sa, NULL);

    _update_display_size();
    nt_erase_erase_screen(NT_COLOR_DEFAULT);
    root = NULL;
}

void nt_display_draw_from_root(enum NTRootDrawOptimization draw_optimization)
{
    if(draw_optimization == NT_ROOT_DRAW_UNOPTIMIZED)
        nt_erase_erase_screen(NT_DISPLAY_DEFAULT_COLOR);

    if(root == NULL) return;

    struct NTConstraints root_constraints;
    nt_constraints_init(&root_constraints, display_width, display_height, display_width, display_height);

    size_t width, height;
    nt_object_draw((struct NTObject*)root, &root_constraints, NT_DRAW_MODE_DRAW, &width, &height);

    nt_object_set_object_position_based_on_dimensions(root, 0, 0, width, height);

    nt_draw_engine_draw(draw_optimization);
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
    // nt_draw_engine_stop_draw();
    struct winsize win_size;
    size_t old_display_height = display_height;
    size_t old_display_width = display_width;

    ioctl(STDIN_FILENO, TIOCGWINSZ, &win_size);

    display_height = win_size.ws_row;
    display_width = win_size.ws_col;

    nt_cursor_conform_pos_to_display();

    nt_draw_engine_on_display_size_change();

    if((display_height < old_display_height) || (display_width < old_display_width))
        nt_display_draw_from_root(NT_ROOT_DRAW_UNOPTIMIZED);
    else
        nt_display_draw_from_root(NT_ROOT_DRAW_OPTIMIZED);

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
