#include <stdio.h>

#include "lib/gds_misc.h"

int gds_misc_max(ssize_t x, ssize_t y)
{
    return (x > y ? x : y);
}

int gds_misc_min(ssize_t x, ssize_t y)
{
    return (x < y ? x : y);
}
