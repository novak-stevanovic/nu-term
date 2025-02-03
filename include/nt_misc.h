#ifndef NT_MISC_H
#define NT_MISC_H

#include <stdlib.h>

ssize_t nt_misc_conform_val(ssize_t min_val, ssize_t val, ssize_t max_val);
double nt_misc_round_double(double x);

#endif
