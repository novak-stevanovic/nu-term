#include "nt_misc.h"

ssize_t nt_misc_conform_val(ssize_t min_val, ssize_t val, ssize_t max_val)
{

    if(val < min_val) return min_val;
    if(val > max_val) return max_val;

    return val;
}

ssize_t nt_misc_min(ssize_t x, ssize_t y)
{
    return (x < y) ? x : y;
}
ssize_t nt_misc_max(ssize_t x, ssize_t y)
{
    return (x > y) ? x : y;
}
