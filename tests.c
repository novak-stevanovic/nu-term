#include <stdio.h>
#include <unistd.h>
#include "nt_core/nt_color.h"
#include "nt_core/nt_display.h"
#include "nt_core/nt_draw_engine.h"
#include "nt_core/nt_erase.h"
#include "nt_derived/nt_solid_color_block.h"
#include "nt_log.h"
#include "nt_misc.h"
#include "nt_primitives/nt_erase_prims.h"
#include "nt_shared/nt_content_matrix.h"

#include "nuterm.h"

#include "nt_base/nt_content_window.h"
#include "nt_derived/nt_progress_bar.h"

#include "nt_base/nt_content_window.h"

#include "termios.h"
#include "nt_derived/nt_hbox_container.h"

void _nt_cw_calculate_required_size_func(struct NTWindow* cw, size_t* x, size_t* y)
{
    struct NTContentWindow* _cw = (struct NTContentWindow*)cw;

    *x = 0;
    *y = 0;
    // *x = nt_content_matrix_get_width(&_cw->_content);
    // *y = nt_content_matrix_get_height(&_cw->_content);
}

void _nt_cw_draw_window_func(struct NTWindow* cw, size_t w, size_t h) 
{
    struct NTContentWindow* _cw = (struct NTContentWindow*)cw;

    if((w == 0) || (h == 0))
    {
        nt_content_matrix_set_size(&_cw->_content, 0, 0);
    }
    else
    {
        nt_content_matrix_set_size(&_cw->_content, h, w);

        int i, j;
        for(i = 0; i < nt_content_matrix_get_height(&_cw->_content); i++)
        {
            for(j = 0; j < nt_content_matrix_get_width(&_cw->_content); j++)
            {
                struct NTDisplayCell* cell = nt_content_matrix_at(&_cw->_content, j, i);
                cell->content = _cw->content;
                cell->bg_color_code = _cw->bg_color;
                cell->fg_color_code = _cw->fg_color;
            }
        }
    }
}


int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);

    nt_init();

    // ------------------------------------------------------------------------------------------------------------

    struct termios t, init_opts;
    tcgetattr(STDIN_FILENO, &init_opts);

    cfmakeraw(&t);
    tcsetattr(STDIN_FILENO, TCSADRAIN, &t);

    // WINDOWS ----------------------------------------------------------------------------------------------

    struct NTSolidColorBlock scb1;
    struct NTSolidColorBlock scb2;
    struct NTProgressBar pb1;

    nt_solid_color_block_init(&scb1, 1);
    nt_solid_color_block_init(&scb2, 2);
    nt_progress_bar_init(&pb1, NT_PROGRESS_BAR_ORIENTATION_HORIZONTAL, 1, 2);

    struct NTObject* _scb1 = (struct NTObject*)&scb1;
    struct NTObject* _scb2 = (struct NTObject*)&scb2;
    struct NTObject* _pb1 = (struct NTObject*)&pb1;

    _scb1->_pref_size_x = 20;
    _scb1->_pref_size_y = 2;

    struct NTHBoxContainer c1;
    nt_hbox_container_init(&c1);

    nt_box_container_add_child((struct NTBoxContainer*)&c1, _scb1);
    nt_box_container_add_child((struct NTBoxContainer*)&c1, _scb2);
    nt_box_container_add_child((struct NTBoxContainer*)&c1, _pb1);

    struct NTObject* _c1 = (struct NTObject*)&c1;
    nt_display_set_root(_c1);

    nt_display_draw_from_root();

    char c = 0;
    while(c != 'q')
    {
        c = getchar();
    }

    nt_erase_erase_screen(NT_COLOR_DEFAULT);
    nt_destruct();

    tcsetattr(STDIN_FILENO, TCSADRAIN, &init_opts);

    return 0;
}
