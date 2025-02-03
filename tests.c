#include <stdio.h>
#include <unistd.h>
#include "api/nt_vec_api.h"
#include "nt_core/nt_color.h"
#include "nt_core/nt_draw_engine.h"
#include "nt_primitives/nt_erase_prims.h"
#include "nt_shared/nt_content_matrix.h"

#include "nuterm.h"

#include "nt_base/nt_content_window.h"

int main(int argc, char *argv[])
{
    // setvbuf(stdout, NULL, _IONBF, 0);
    //
    // nt_eprim_erase_screen();
    // nt_init();
    // char c;
    //
    // struct NTContentWindow w;
    // nt_content_window_init(&w, NULL);
    //
    // struct NTObject* _w = (struct NTObject*)&w;
    //
    // _w->_rel_start_x = 0;
    // _w->_rel_start_y = 0;
    //
    // _w->_rel_end_x = 100;
    // _w->_rel_end_y = 10;
    //
    // nt_content_matrix_set_size(&w._content, 11, 101);
    //
    // int i, j;
    // for(i = 0; i < 11; i++)
    // {
    //     for(j = 0; j < 101; j++)
    //     {
    //         struct NTDisplayCell* curr_cell = (struct NTDisplayCell*)nt_content_matrix_at(&w._content, j, i);
    //
    //         curr_cell->content = 'a' + i;
    //         curr_cell->bg_color_code = 0;
    //         curr_cell->fg_color_code = 5;
    //     }
    // }
    //
    // nt_draw_engine_add_window_to_draw_queue((struct NTWindow*)&w);
    // nt_draw_engine_draw();
    //
    // // nt_display_get_display_width
    // read(STDIN_FILENO, &c, 1);
    //
    // nt_eprim_erase_screen();
}
