#include <stdlib.h>
#include <assert.h>

#include "nt_shared/nt_display_cell.h"

void nt_display_cell_assign(struct NTDisplayCell* dest, struct NTDisplayCell* src)
{
    assert(dest != NULL);
    assert(src != NULL);

    *dest = *src;
}
