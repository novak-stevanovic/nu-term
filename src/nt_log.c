#include <stdio.h>

#include "nt_log.h"

FILE* _f;

void nt_log_init()
{
    _f = fopen("/home/novak/Documents/nt_log.txt", "w");

    setvbuf(_f, NULL, _IONBF, 0);
    fprintf(_f, "------------------- LOGGING BEGINNING -------------------\n");
}

void nt_log_destruct()
{
    fprintf(_f, "------------------- LOGGING END -------------------\n");
    fclose(_f);
}

void nt_log_log(char* text, ...)
{
    va_list args;
    va_start(args, text);
    vfprintf(_f, text, args);
    va_end(args);
}

