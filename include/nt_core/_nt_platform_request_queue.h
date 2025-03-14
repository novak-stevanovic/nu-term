#ifndef __NT_PLATFORM_REQUEST_QUEUE_H__
#define __NT_PLATFORM_REQUEST_QUEUE_H__

#include "nt_core/nt_platform.h"

#include <stdlib.h>
#include <pthread.h>

struct NTObject;
typedef struct NTObject NTObject;

typedef struct NTPlatformRequest
{
    void (*_perform_func)(void* data);
    char _data[NT_PLATFORM_REQ_DATA_MAX_SIZE];
} NTPlatformRequest;

typedef struct NTPlatformRequestQueue
{
    ssize_t _head, _tail;

    pthread_mutex_t _lock;

    /* The memory pool with the capacity to store REQUEST_CAPACITY elements
     * will be alloced in _nt_platform_req_queue_init() function.
     * This memory pool will be used for allocating memory for
     * NTPlatformRequests. 
     * This is done because the queue must be async-safe which requires
     * no malloc() calls in push_back() and pop_head() functions. */
    NTPlatformRequest* __request_mem_pool;
} NTPlatformRequestQueue;

void _nt_platform_req_queue_init(NTPlatformRequestQueue* queue);
void _nt_platform_req_queue_destroy(NTPlatformRequestQueue* queue);

// ASYNC-SAFE
void _nt_platform_req_queue_push_back(NTPlatformRequestQueue* queue,
        void (*perform_func)(void* data), void* data, size_t data_size);

// ASYNC-SAFE
void _nt_platform_request_queue_pop_front(NTPlatformRequestQueue* queue,
        void (**out_perform_func)(void* data), void** out_data);

// ASYNC-SAFE - TODO: fix(check src file)
void _nt_platform_req_queue_push_front(NTPlatformRequestQueue* queue,
        void (*perform_func)(void* data), void* data, size_t data_size);

// ASYNC-SAFE
void _nt_platform_request_queue_get_count(NTPlatformRequestQueue* queue,
        size_t* out_request_count);

#endif // __NT_PLATFORM_REQUEST_QUEUE_H__
