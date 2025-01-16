#ifndef NT_DISPLAY_CELL_H
#define NT_DISPLAY_CELL_H

#include <stddef.h>

struct NTDisplayCell
{
    size_t fg_color_code, bg_color_code;
    char content;
};

// container:
// obj.sx = x
// obj.sy = y
//
// obj.draw
//
// obj2.sx = x2
// obj2.sy = y2
//
// obj2.draw
//
// stanca
//
// return u obj.draw
//
// tc_draw_obj:
//
// if(can_be_drawn(obj))
//     obj->draw(size_t needed_x, size_t needed_y)
// else
//     obj->nodraw()
//

//
// dynamic_container:
//
// start_x, start_y = 0
// size_needed_x, size_needed_y;
// for child in children:
//     max_size_x, max_size_y = tc_container_get_max_size_for_child(child)
//     obj_draw(child, &size_needed_x, &size_needed_y, start_x, start_y, max_size_x, max_size_y);




#endif
