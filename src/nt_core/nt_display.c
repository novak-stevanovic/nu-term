#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <asm/termbits.h>
#include <sys/ioctl.h>

#include "nt_core/nt_display.h"
#include "nt_base/nt_object.h"
#include "nt_core/nt_cursor.h"
#include "nt_core/nt_erase.h"
#include "nt_core/nt_draw_engine.h"
#include "nt_core/nt_erase.h"

#define SIGWINCH 28

static void _update_display_size();
static void _sigwinch_sa_handler(int signum);
static void _set_root_bounds();

// ---------------------------------------------------------------------------------------------------------

size_t display_height, display_width;

struct NTObject* root;

void nt_display_init()
{
    struct sigaction sa = {0};
    sa.sa_handler = &_sigwinch_sa_handler;

    sigaction(SIGWINCH, &sa, NULL);

    _update_display_size();
    nt_erase_erase_screen();
    root = NULL;
}

void nt_display_draw_from_root()
{
    if(root == NULL) return;

    root->_tainted = true;
    nt_draw_engine_draw_object_tree(root);
}

void nt_display_set_root(struct NTObject* new_root)
{
    root = new_root;

    _set_root_bounds();
    root->_tainted = true;
    
    nt_draw_engine_draw_object_tree(root);
}

struct NTObject* nt_display_get_root()
{
    return root;
}

size_t nt_display_get_width()
{
    return display_width;
}

size_t nt_display_get_height()
{
    return display_height;
}

static void _update_display_size()
{
    struct winsize win_size;
    size_t old_display_height = display_height;
    size_t old_display_width = display_width;

    ioctl(STDIN_FILENO, TIOCGWINSZ, &win_size);

    display_height = win_size.ws_row;
    display_width = win_size.ws_col;

    nt_draw_engine_on_display_size_change();

    nt_cursor_conform_pos_to_display();

    nt_erase_erase_screen();
    nt_erase_erase_scollback_buffer();

    if(root)
    {
        _set_root_bounds();
        nt_draw_engine_draw_object_tree(root);
    }
}

static void _sigwinch_sa_handler(int signum)
{
    _update_display_size();
}

int nt_display_is_in_bounds(size_t x, size_t y)
{
    return (x < display_width) && (y < display_height);
}

static void _set_root_bounds()
{
    NTBounds new_root_bounds;
    nt_bounds_init(&new_root_bounds, 0, 0, display_width, display_height);

    nt_object_set_position(root, &new_root_bounds);
}
