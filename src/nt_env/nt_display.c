#include <signal.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "nt_env/nt_display.h"
#include "nt_env/base/nt_cursor.h"

static size_t display_width, display_height;

static void _update_display_size();
static void _sigwinch_sa_handler(int signum);

void nt_display_init()
{
    struct sigaction sa = {0};
    sa.sa_handler = &_sigwinch_sa_handler;

    sigaction(SIGWINCH, &sa, NULL);

    _update_display_size();
}

void nt_display_destruct()
{
    display_width = 0;
    display_height = 0;
}

size_t nt_display_get_width()
{
    return display_width;
}

size_t nt_display_get_height()
{
    return display_height;
}

static void _sigwinch_sa_handler(int signum)
{
    _update_display_size();
}

static void _update_display_size()
{
    struct winsize win_size;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &win_size);

    display_height = win_size.ws_row;
    display_width = win_size.ws_col;

    nt_cursor_conform_pos_to_display();
}
