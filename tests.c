#include "nt_component/derived/nt_solid_color_block.h"
#include "nt_env/base/nt_gfx.h"
#include "nt_env/nt_display.h"
#include "nt_env/nt_display.h"
#include "nuterm.h"
#include <stdio.h>
#include <unistd.h>

int main()
{
    // ------------------------------------------------------------------------------------------------------------

    nuterm_init(NULL);

    NTSolidColorBlock scb;
    NTColor white = nt_color_create_tc(255, 255, 255);
    nt_solid_color_block_init(&scb, white);

    nt_display_set_root((NTObject*)&scb);

    char c;
    while((c = getchar()) != 'q')
    {
        // putchar(c);
    }

    nuterm_destruct();

    return 0;
}
