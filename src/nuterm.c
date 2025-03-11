#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "nuterm.h"
#include "nt_env/base/nt_cursor.h"
#include "nt_env/base/nt_gfx.h"
#include "nt_env/base/nt_screen.h"
#include "nt_env/nt_display.h"

static struct termios init_opts;

void _term_opts_init()
{
    tcgetattr(STDIN_FILENO, &init_opts);

    struct termios t;
    cfmakeraw(&t);
    tcsetattr(STDIN_FILENO, TCSADRAIN, &t);
}

void _term_opts_destruct()
{
    tcsetattr(STDIN_FILENO, TCSADRAIN, &init_opts);
}

void nuterm_init()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    _term_opts_init();

    nt_screen_init();
    nt_cursor_init(); // first init cursor, then display
    nt_display_init();
    nt_gfx_init();
}

void nuterm_destruct()
{
    nt_gfx_destruct();
    nt_cursor_destruct();
    nt_display_destruct();

    nt_screen_destruct();
    _term_opts_destruct();
}
