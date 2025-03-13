#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include "nt_util/nt_log.h"

static pthread_mutex_t _log_lock;

static FILE* _logs_f = NULL;

static inline void _print_thread()
{
    fprintf(_logs_f, "TID: %lu | ", (unsigned long) pthread_self());
}

void nt_log_init(char* _logs_fpath)
{
    pthread_mutex_init(&_log_lock, NULL);

    _logs_f = fopen(_logs_fpath, "a");

    if(_logs_f == NULL) return; 
    setvbuf(_logs_f, NULL, _IOLBF, 50);
    
    nt_log("LOGGING BEGINNING");
}

void nt_log(const char* format, ...) 
{
    if(_logs_f == NULL) return; 

    pthread_mutex_lock(&_log_lock);

    time_t now = time(NULL);
    struct tm* t = localtime(&now);

    _print_thread();
    fprintf(_logs_f, "[%02d:%02d:%02d] ", t->tm_hour, t->tm_min, t->tm_sec);

    va_list args;
    va_start(args, format);
    vfprintf(_logs_f, format, args);
    va_end(args);

    fprintf(_logs_f, "\n");

    pthread_mutex_unlock(&_log_lock);
}

void nt_log_destruct()
{
    if(_logs_f == NULL) return; 

    nt_log("LOGGING END");
    fclose(_logs_f);

    pthread_mutex_destroy(&_log_lock);
}
