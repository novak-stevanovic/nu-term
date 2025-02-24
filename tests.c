#include <stdio.h>
#include <unistd.h>
#include "nt_core/nt_color.h"
#include "nt_core/nt_display.h"
#include "nt_core/nt_draw_engine.h"
#include "nt_core/nt_erase.h"
#include "nt_derived/nt_hbox_container.h"
#include "nt_derived/nt_solid_color_block.h"
#include "nt_log.h"
#include "nt_misc.h"
#include "nt_primitives/nt_erase_prims.h"
#include "nt_shared/nt_content_matrix.h"

#include "nuterm.h"

#include "nt_derived/nt_progress_bar.h"


#include "termios.h"

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);

    nt_init();

    // ------------------------------------------------------------------------------------------------------------

    struct termios t, init_opts;
    tcgetattr(STDIN_FILENO, &init_opts);

    cfmakeraw(&t);
    tcsetattr(STDIN_FILENO, TCSADRAIN, &t);

    // ----------------------------------------------------------------------------------------------
    //

    struct NTSolidColorBlock scb11;
    struct NTSolidColorBlock scb22;
    struct NTObject* _scb11 = (struct NTObject*)&scb11;
    struct NTObject* _scb22 = (struct NTObject*)&scb22;

    nt_solid_color_block_init(&scb11, 1, NT_DRAW_ENGINE_HIGH_DRAW_PRIORITY);
    nt_solid_color_block_init(&scb22, 2, NT_DRAW_ENGINE_HIGH_DRAW_PRIORITY);

    _scb11->_pref_width = 10;
    _scb11->_pref_height = 4;

    _scb22->_pref_width = 6;
    _scb22->_pref_height = 8;

    struct NTHBoxContainer c11;
    struct NTBoxContainer* __c11 = (struct NTBoxContainer*)&c11;
    nt_hbox_container_init(&c11);

    // __c11->_padding.north = 3;
    __c11->_padding.west = 5;
    __c11->_spacing = 2;

    ((struct NTObject*)&c11)->_pref_width = 50;
    ((struct NTObject*)&c11)->_pref_height = 20;

    nt_box_container_add_child(__c11, _scb11);
    nt_box_container_add_child(__c11, _scb22);

    // ----------------------------------------------------------------------------------------------

    struct NTSolidColorBlock scb1;
    struct NTSolidColorBlock scb2;
    struct NTSolidColorBlock scb3;
    struct NTProgressBar pb1;

    nt_solid_color_block_init(&scb1, 1, NT_DRAW_ENGINE_HIGH_DRAW_PRIORITY);
    nt_solid_color_block_init(&scb2, 2, NT_DRAW_ENGINE_HIGH_DRAW_PRIORITY);
    nt_progress_bar_init(&pb1, NT_PROGRESS_BAR_ORIENTATION_HORIZONTAL, 1, 2, NT_DRAW_ENGINE_HIGH_DRAW_PRIORITY);
    nt_solid_color_block_init(&scb3, 3, NT_DRAW_ENGINE_HIGH_DRAW_PRIORITY);

    nt_progress_bar_set_progress(&pb1, 25);

    struct NTObject* _scb1 = (struct NTObject*)&scb1;
    struct NTObject* _scb2 = (struct NTObject*)&scb2;
    struct NTObject* _scb3 = (struct NTObject*)&scb3;
    struct NTObject* _pb1 = (struct NTObject*)&pb1;

    _scb1->_pref_width = 30;
    _scb1->_pref_height = 10;

    _scb2->_pref_width = 10;
    _scb2->_pref_height = 20;

    _scb3->_pref_height = 15;
    _scb3->_pref_width = 20;

    _pb1->_pref_width = 40;
    _pb1->_pref_height = 1;

    struct NTHBoxContainer c1;
    struct NTBoxContainer* __c1 = (struct NTBoxContainer*)&c1;
    nt_hbox_container_init(&c1);
    nt_container_set_background_color((struct NTContainer*)&c1, 4);
    nt_container_set_background_color((struct NTContainer*)&c11, 5);

    __c1->_padding.north = 2;
    __c1->_padding.west = 5;
    __c1->_padding.east = 5;
    __c1->_padding.south = 2;
    __c1->_spacing = 5;

    nt_box_container_add_child(__c1, (struct NTObject*)&c11);
    nt_box_container_add_child(__c1, _scb1);
    nt_box_container_add_child(__c1, _scb2);
    nt_box_container_add_child(__c1, _pb1);
    nt_box_container_add_child(__c1, _scb3);

    struct NTObject* _c1 = (struct NTObject*)&c1;
    nt_display_set_root(_c1);

    nt_display_draw_from_root(NT_ROOT_DRAW_UNOPTIMIZED);

    char c = 0;
    while(true)
    {
        c = getchar();

        if(c == 'q') break;
        else if(c == '1') // big container
        {
            c = getchar();
            if(c == 'm') // change main axis
            {
                c = getchar();
                if(c == '1') ((struct NTBoxContainer*)&c1)->_main_axis_alignment = NT_BOX_CONTAINER_MAIN_AXIS_ALIGNMENT_START;
                else if(c == '2') ((struct NTBoxContainer*)&c1)->_main_axis_alignment = NT_BOX_CONTAINER_MAIN_AXIS_ALIGNMENT_CENTER;
                else if(c == '3') ((struct NTBoxContainer*)&c1)->_main_axis_alignment = NT_BOX_CONTAINER_MAIN_AXIS_ALIGNMENT_END;
                nt_display_draw_from_root(NT_ROOT_DRAW_UNOPTIMIZED);
            }
            if(c == 's') // change secondary axis
            {
                c = getchar();
                if(c == '1') ((struct NTBoxContainer*)&c1)->_secondary_axis_alignment = NT_BOX_CONTAINER_SECONDARY_AXIS_ALIGNMENT_START;
                else if(c == '2') ((struct NTBoxContainer*)&c1)->_secondary_axis_alignment = NT_BOX_CONTAINER_SECONDARY_AXIS_ALIGNMENT_CENTER;
                else if(c == '3') ((struct NTBoxContainer*)&c1)->_secondary_axis_alignment = NT_BOX_CONTAINER_SECONDARY_AXIS_ALIGNMENT_END;
                nt_display_draw_from_root(NT_ROOT_DRAW_UNOPTIMIZED);
            }
        }
        else if(c == '2') // small container
        {
            c = getchar();
            if(c == 'm') // change main axis
            {
                c = getchar();
                if(c == '1') ((struct NTBoxContainer*)&c11)->_main_axis_alignment = NT_BOX_CONTAINER_MAIN_AXIS_ALIGNMENT_START;
                else if(c == '2') ((struct NTBoxContainer*)&c11)->_main_axis_alignment = NT_BOX_CONTAINER_MAIN_AXIS_ALIGNMENT_CENTER;
                else if(c == '3') ((struct NTBoxContainer*)&c11)->_main_axis_alignment = NT_BOX_CONTAINER_MAIN_AXIS_ALIGNMENT_END;
                nt_display_draw_from_root(NT_ROOT_DRAW_UNOPTIMIZED);
            }
            if(c == 's') // change secondary axis
            {
                c = getchar();
                if(c == '1') ((struct NTBoxContainer*)&c11)->_secondary_axis_alignment = NT_BOX_CONTAINER_SECONDARY_AXIS_ALIGNMENT_START;
                else if(c == '2') ((struct NTBoxContainer*)&c11)->_secondary_axis_alignment = NT_BOX_CONTAINER_SECONDARY_AXIS_ALIGNMENT_CENTER;
                else if(c == '3') ((struct NTBoxContainer*)&c11)->_secondary_axis_alignment = NT_BOX_CONTAINER_SECONDARY_AXIS_ALIGNMENT_END;
                nt_display_draw_from_root(NT_ROOT_DRAW_UNOPTIMIZED);
            }
        }
        else if(c == 'r') nt_display_draw_from_root(NT_ROOT_DRAW_UNOPTIMIZED);
    }

    // char c;
    // while(1)
    // {
    //     c = getchar();
    //     if(c == 'q')
    //         break;
    // }
    fflush(stdout);
    tcsetattr(STDIN_FILENO, TCSADRAIN, &init_opts);

    nt_erase_erase_screen(NT_COLOR_DEFAULT);
    nt_destruct();

    setvbuf(stdout, NULL, _IONBF, 0);
    return 0;
}
