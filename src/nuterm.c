#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "nuterm.h"
#include "nt_core/platform/nt_platform.h"
#include "nt_core/engine/nt_draw_engine.h"
#include "nt_env/nt_cursor.h"
#include "nt_env/nt_gfx.h"
#include "nt_env/nt_screen.h"
#include "nt_core/display/nt_display.h"
#include "nt_util/nt_log.h"

static struct termios init_opts;
static bool _log_enabled = false;

void _term_opts_init()
{
    tcgetattr(STDIN_FILENO, &init_opts);

    struct termios t;
    cfmakeraw(&t);
    tcsetattr(STDIN_FILENO, TCSADRAIN, &t);
}

void _term_opts_destroy()
{
    tcsetattr(STDIN_FILENO, TCSADRAIN, &init_opts);
}

void nuterm_init(char* logs_filepath)
{
    if(logs_filepath != NULL)
    {
        nt_log_init(logs_filepath);
        _log_enabled = true;
    }

    setvbuf(stdout, NULL, _IONBF, 0);
    _term_opts_init();

    _nt_platform_init();
    _nt_screen_init();
    _nt_cursor_init(); // first init cursor, then display
    _nt_display_init(); // first init display, then draw engine
    _nt_draw_engine_init();
    _nt_gfx_init();
}

void nuterm_destruct()
{
    _nt_platform_destroy();
    _nt_gfx_destroy();
    _nt_cursor_destroy();
    _nt_display_destroy();
    _nt_draw_engine_destroy();

    _nt_screen_destroy();
    _term_opts_destroy();

    if(_log_enabled)
    {
        _nt_log_destroy();
        _log_enabled = false;
    }
}
