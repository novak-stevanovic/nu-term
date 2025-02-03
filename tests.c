#include <stdio.h>
#include <unistd.h>
#include "api/nt_vec_api.h"
#include "nt_base/nt_layout_container.h"
#include "nt_core/nt_color.h"
#include "nt_core/nt_display.h"
#include "nt_core/nt_draw_engine.h"
#include "nt_derived/nt_solid_color_block.h"
#include "nt_primitives/nt_erase_prims.h"
#include "nt_shared/nt_content_matrix.h"

#include "nuterm.h"

#include "nt_base/nt_content_window.h"
#include "nt_derived/nt_layout_managers/nt_simple_layout_manager.h"

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);

    nt_init();

    struct NTSolidColorBlock cb;
    struct NTLayoutContainer lc;
    struct NTSimpleLayoutManager slm;

    // ((struct NTObject*)&cb)->_min_size_x = 100;

    nt_solid_color_block_init(&cb, 4);
    nt_layout_container_init(&lc, (struct NTLayoutManager*)&slm);
    nt_simple_layout_manager_init(&slm, &lc); 

    nt_simple_layout_manager_set_container_child(&slm, (struct NTObject*)&cb);

    nt_display_set_root((struct NTContainer*)&lc);
    slm._padding_object.north = 2;
    slm._padding_object.east = 10;
    slm._padding_object.west = 2;
    slm._padding_object.south = 40;

    nt_display_draw_from_root();
    nt_draw_engine_draw();
    getchar();
}
