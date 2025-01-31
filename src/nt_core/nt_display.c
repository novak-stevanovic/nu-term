#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <asm/termbits.h>
#include <sys/ioctl.h>
#include <assert.h>

#include "nt_core/nt_display.h"
#include "nt_core/nt_cursor.h"

#define SIGWINCH 28

static void _update_display_size();
static void _sigwinch_sa_handler(int signum);

// ---------------------------------------------------------------------------------------------------------

size_t display_height, display_width;

void nt_display_init()
{
    struct sigaction sa = {0};
    sa.sa_handler = &_sigwinch_sa_handler;

    int sigact_status = sigaction(SIGWINCH, &sa, NULL);
    assert(sigact_status == 0);

    _update_display_size();
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
}

static void _sigwinch_sa_handler(int signum)
{
    _update_display_size();
}

int nt_display_is_in_bounds(size_t x, size_t y)
{
    return (x < display_width) && (y < display_height);
}
