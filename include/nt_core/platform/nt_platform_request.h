#ifndef _NT_PLATFORM_REQUEST_H_
#define _NT_PLATFORM_REQUEST_H_

#include <stddef.h>

#define NT_PLATFORM_REQUEST_MAX_DATA_SIZE 100

typedef struct NTPlatformRequest
{
    void (*_perform_func)(void* data);
    char _data[NT_PLATFORM_REQUEST_MAX_DATA_SIZE];
} NTPlatformRequest;

/* TODO: introduce error handling for (data_size >
 * NT_PLATFORM_REQUEST_MAX_DATA_SIZE) */

void nt_platform_request_init(NTPlatformRequest* request, 
        void (*perform_func)(void* data),
        void* data, size_t data_size);

#endif // _NT_PLATFORM_REQUEST_H_
