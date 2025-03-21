#include "nt_component/derived/nt_solid_color_block.h"
#include "nt_env/base/nt_gfx.h"
#include "nt_env/nt_display.h"
#include "nt_env/nt_display.h"
#include "nuterm.h"
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    // ------------------------------------------------------------------------------------------------------------

    nuterm_init("nt_log.txt");

    NTSolidColorBlock scb;
    NTColor curr_color = nt_color_create_c256(0);
    nt_solid_color_block_init(&scb, curr_color);

    nt_display_set_root((NTObject*)&scb);
    //
    char c;
    uint8_t curr_color_val = 0;
    size_t i = 0;
    while(i < (500))
    {
        usleep(10000);
        curr_color = nt_color_create_c256(curr_color_val);
        nt_solid_color_block_set_color(&scb, curr_color);
        curr_color_val++;
        i++;
    }

    while(getchar() != 'q');

    nuterm_destruct();

    return 0;
}
