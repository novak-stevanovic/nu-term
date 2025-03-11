#ifndef _NT_MISC_H_
#define _NT_MISC_H_

#include <stdlib.h>

ssize_t nt_misc_conform_ssize(ssize_t min_val, ssize_t val, ssize_t max_val);
double nt_misc_conform_double(double min_val, double val, double max_val);

ssize_t nt_misc_min(ssize_t x, ssize_t y);
ssize_t nt_misc_max(ssize_t x, ssize_t y);

#endif // _NT_MISC_H_
