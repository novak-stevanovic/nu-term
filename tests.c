#include <stdio.h>
#include <unistd.h>
#include "nt_core/nt_display.h"
#include "nt_core/nt_erase.h"

#include "nt_derived/nt_progress_bar.h"
#include "nuterm.h"

#include "termios.h"

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);

    nt_init();

    // ----------------------------------------------------------------------------------------------

    struct termios t, init_opts;
    tcgetattr(STDIN_FILENO, &init_opts);

    cfmakeraw(&t);
    tcsetattr(STDIN_FILENO, TCSADRAIN, &t);

    // ----------------------------------------------------------------------------------------------

    NTProgressBar pb1;
    nt_progress_bar_init(&pb1, NT_ORIENTATION_HORIZONTAL, 2, 1);

    nt_progress_bar_set_progress(&pb1, 0.5);

    NTObject* _pb1 = (NTObject*)&pb1;

    nt_display_set_root(_pb1);

    while(getchar() != 'q');

    // ----------------------------------------------------------------------------------------------

    tcsetattr(STDIN_FILENO, TCSADRAIN, &init_opts);

    nt_destruct();

    setvbuf(stdout, NULL, _IONBF, 0);
    return 0;
}
