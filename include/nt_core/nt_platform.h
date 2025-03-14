#ifndef _NT_PLATFORM_H_
#define _NT_PLATFORM_H_

#include <stddef.h>
#define NT_PLATFORM_REQ_DATA_MAX_SIZE 100

/* NTPlatform is a module that allows for GUI updates to run on the designated
 * NTPlatform thread. Any changes to any GUI element(any NTObject) should
 * be performed via the nt_platform_execute() function(except NTObject
 * initialization). This also applies to changes to NTDisplay buffer.
 * This is to avoid race conditions. */

void _nt_platform_init();

void _nt_platform_destroy();

/* Adds a request to the queue for execution. If this function was called
 * from NTPlatformThread, the request will be processed immediately. Otherwise,
 * the request will be processed after all queued requests have been processed.
 * Thread-safe. Async-safe. */
void nt_platform_execute(void (*request_func)(void* data),
        void* data, size_t data_size);

void nt_platform_execute_first(void (*request_func)(void* data),
        void* data, size_t data_size);

#endif // _NT_PLATFORM_H_
