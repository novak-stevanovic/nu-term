#ifndef NT_LOG_H
#define NT_LOG_H

#include <stdarg.h>

void nt_log_init();
void nt_log_destruct();
void nt_log_log(char* text, ...);

#endif
