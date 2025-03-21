#ifndef __NT_PLATFORM_REQUEST_QUEUE_H__
#define __NT_PLATFORM_REQUEST_QUEUE_H__

#include <stddef.h>
#include <pthread.h>

typedef struct NTPlatformRequest NTPlatformRequest;
typedef struct SArena SArena;

typedef struct NTPlatformRequestQueue
{
    struct NTPlatformRequestNode* _head;
    struct NTPlatformRequestNode* _tail;

    size_t _count;

    pthread_mutex_t _lock;
    SArena* _arena;
} NTPlatformRequestQueue;

void nt_platform_request_queue_init(NTPlatformRequestQueue* queue);

void nt_platform_request_queue_destroy(NTPlatformRequestQueue* queue);

void nt_platform_request_queue_push_back(NTPlatformRequestQueue* queue,
        NTPlatformRequest* request);

void nt_platform_request_queue_get_head(NTPlatformRequestQueue* queue,
        NTPlatformRequest** out_request);

void nt_platform_request_queue_pop_front(NTPlatformRequestQueue* queue);

void nt_platform_request_queue_get_count(NTPlatformRequestQueue* queue,
        size_t *out_count);

#endif // __NT_PLATFORM_REQUEST_QUEUE_H__
