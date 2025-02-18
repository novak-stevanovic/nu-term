#ifndef NT_CONSTRAINTS_H
#define NT_CONSTRAINTS_H

#include <stdlib.h>

/* Object that represents size constraints given to an NTObject when the NTObject is being drawn.
 * The caller(usually the parent) will determine minimum and maximum height and width for an object that is supposed to be drawn. 
 * The caller will invoke nt_object_draw(NTObject object, NTConstraints constraints). The drawn object must respect these constraints, no matter
 * its properties(min, max, pref size... etc). When the drawn object finishes drawing, it should set the used_x and used_y fields inside
 * the NTConstraints struct to tell the caller how much of the allocated space it had used. */
struct NTConstraints
{
    size_t _min_width, _min_height; // read-only
    size_t _max_width, _max_height; // read-only

    ssize_t _used_x, _used_y;
};

void nt_constraints_init(struct NTConstraints* constraints,
        size_t min_width, size_t min_height,
        size_t max_width, size_t max_height);

int nt_constraints_check_consistency(struct NTConstraints* constraints);

int nt_constraints_has_object_been_drawn(size_t used_x, size_t used_y);
int nt_constraints_has_object_been_drawn_c(struct NTConstraints* constraints);

void nt_constraints_set_values(struct NTConstraints* constraints, size_t used_x, size_t used_y);

#endif
