#ifndef _GDS_MISC_H_
#define _GDS_MISC_H_

#include "gds.h"
#include <stdio.h>

int gds_misc_max(ssize_t x, ssize_t y);
int gds_misc_min(ssize_t x, ssize_t y);
void gds_misc_swap(void* data1, void* data2, void* swap_buff, size_t data_size);

// ---------------------------------------------------------------------------------------------------------------------

#endif
