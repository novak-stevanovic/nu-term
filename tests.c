#include "nt_env/base/nt_cursor.h"
#include "nt_env/base/nt_gfx.h"
#include "nt_shared/nt_display_cell.h"
#include "nuterm.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    // ------------------------------------------------------------------------------------------------------------

    nuterm_init();

    NTDisplayCell buffer_to_draw[35][35];
    size_t i, j;

    for(i = 0; i < 35; i++)
    {
        for(j = 0; j < 35; j++)
            nt_display_cell_init_default(&buffer_to_draw[i][j]);
    }

    for(i = 0; i < 35; i++)
    {
        for(j = 0; j < 35; j++)
        {
            if((j == 0) || (j == 34) || (i == j))
                buffer_to_draw[i][j]._content = 'e';
        }
    }

    NTColor red = nt_color_create_c256(1);
    NTStyle bold_and_italic = NT_STYLE_BOLD | NT_STYLE_ITALIC;
    NTStyle italic = NT_STYLE_ITALIC;

    nt_color_set_fg(red);
    nt_style_set(italic);
    for(i = 0; i < 35; i++)
    {
        for(j = 0; j < 35; j++)
        {
            nt_cursor_abs_move_to_xy(j, i);

            // nt_gfx_color(buffer_to_draw[i][j]._bg_color);
            // nt_color_set_fg_color(buffer_to_draw[i][j]._fg_color);
            putchar(buffer_to_draw[i][j]._content);
        }
    }

    char c;
    while((c = getchar()) != 'q')
    {
        putchar(c);
    }

    nuterm_destruct();

    return 0;
}
