#include <stdio.h>
#include <unistd.h>
#include "api/nt_vec_api.h"
#include "nt_base/nt_layout_container.h"
#include "nt_core/nt_color.h"
#include "nt_core/nt_display.h"
#include "nt_core/nt_draw_engine.h"
#include "nt_core/nt_erase.h"
#include "nt_derived/nt_solid_color_block.h"
#include "nt_primitives/nt_erase_prims.h"
#include "nt_shared/nt_content_matrix.h"

#include "nuterm.h"

#include "nt_base/nt_content_window.h"
#include "nt_derived/nt_layout_managers/nt_simple_layout_manager.h"
#include "nt_derived/nt_progress_bar.h"

#include "nt_base/nt_content_window.h"

#include "termios.h"

void _nt_cw_calculate_required_size_func(struct NTWindow* cw, size_t* x, size_t* y)
{
    struct NTContentWindow* _cw = (struct NTContentWindow*)cw;

    *x = nt_content_matrix_get_width(&_cw->_content);
    *y = nt_content_matrix_get_height(&_cw->_content);
}

void _nt_cw_draw_window_func(struct NTWindow* cw, size_t w, size_t h) 
{
    struct NTContentWindow* _cw = (struct NTContentWindow*)cw;

    nt_content_matrix_set_size(&_cw->_content, h, w);
    // printf("drawing cw\n");
}


int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);

    nt_init();

    // struct NTProgressBar pb;
    // struct NTLayoutContainer lc;
    // struct NTSimpleLayoutManager slm;
    //
    // nt_progress_bar_init(&pb, NT_PROGRESS_BAR_ORIENTATION_HORIZONTAL, 2, 3);
    // nt_layout_container_init(&lc);
    // nt_simple_layout_manager_init(&slm, &lc); 
    //
    // pb._base._base._pref_size_x = 5000;
    // pb._base._base._pref_size_y = 2000;
    //
    // // pb._base._base._max_size_x = 10;
    // // pb._base._base._max_size_y = 10;
    //
    // nt_layout_container_set_layout_manager(&lc, (struct NTLayoutManager*)&slm);
    //
    // nt_simple_layout_manager_set_container_child(&slm, (struct NTObject*)&pb);
    //
    // nt_display_set_root((struct NTObject*)&lc);
    // slm._padding_object.north = 0;
    // slm._padding_object.east = 20;
    // slm._padding_object.west = 0;
    // slm._padding_object.south = 0;
    //
    // pb._progress = 29.5;
    //
    // nt_display_draw_from_root();
    // nt_draw_engine_draw();
    // getchar();

    // ------------------------------------------------------------------------------------------------------------

    struct termios t, init_opts;
    tcgetattr(STDIN_FILENO, &init_opts);

    cfmakeraw(&t);
    tcsetattr(STDIN_FILENO, TCSADRAIN, &t);

    struct NTContentWindow cw;
    struct NTObject* _cw = (struct NTObject*)&cw;
    struct NTLayoutContainer lc;
    struct NTObject* _lc = (struct NTObject*)&lc;
    struct NTSimpleLayoutManager slm;

    nt_content_window_init(&cw, _nt_cw_calculate_required_size_func, _nt_cw_draw_window_func);
    nt_layout_container_init(&lc);
    nt_simple_layout_manager_init(&slm);

    // printf("EXISTING OBJECTS: %p %p %p\n", &cw, &lc, &slm);

    _cw->_pref_size_x = 20;
    _cw->_pref_size_y = 10;

    nt_simple_layout_manager_set_child(&slm, _cw);
    nt_layout_container_set_layout_manager(&lc, (struct NTLayoutManager*)&slm);
    nt_container_set_background_color((struct NTContainer*)&lc, 3);

    nt_display_set_root(_lc);

    nt_display_draw_from_root();

    char c;
    while((c = getchar()) != 'q')
    {
        if(c == 'h')
        {
            nt_object_set_pref_size_x(_cw, (int)nt_object_get_pref_size_x(_cw) - 10);
        }
        if(c == 'k')
        {
            nt_object_set_pref_size_y(_cw, (int)nt_object_get_pref_size_y(_cw) - 5);
        }
        if(c == 'j')
        {
            nt_object_set_pref_size_y(_cw, (int)nt_object_get_pref_size_y(_cw) + 5);
        }
        if(c == 'l')
        {
            nt_object_set_pref_size_x(_cw, (int)nt_object_get_pref_size_x(_cw) + 10);
        }

        // printf("next\n");
        nt_erase_erase_screen(NT_COLOR_DEFAULT);
        nt_display_draw_from_root();
    }

    nt_erase_erase_screen(NT_COLOR_DEFAULT);

    tcsetattr(STDIN_FILENO, TCSADRAIN, &init_opts);
    return 0;
}
