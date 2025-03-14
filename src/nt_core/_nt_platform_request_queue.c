#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "nt_core/_nt_platform_request_queue.h"
#include "nt_util/nt_log.h"
#include "pthread.h"

#define REQUEST_QUEUE_CAPACITY 1000000

#define NO_HEAD -1
#define NO_TAIL -1

// TODO: Make producer-consumer style buffer

void _nt_platform_req_queue_init(NTPlatformRequestQueue* queue)
{
    queue->_head = NO_HEAD;
    queue->_tail = NO_TAIL;
    queue->__request_mem_pool = malloc(sizeof(NTPlatformRequest) * REQUEST_QUEUE_CAPACITY);

    assert(queue->__request_mem_pool != NULL);
    
    pthread_mutex_init(&queue->_lock, NULL);
}

void _nt_platform_req_queue_destroy(NTPlatformRequestQueue* queue)
{
    queue->_head = NO_HEAD;
    queue->_tail = NO_TAIL;

    if(queue->__request_mem_pool) free(queue->__request_mem_pool);

    pthread_mutex_destroy(&queue->_lock);
}

void _nt_platform_req_queue_push_back(NTPlatformRequestQueue* queue,
        void (*perform_func)(void* data), void* data, size_t data_size)
{
    pthread_mutex_lock(&queue->_lock);

    if(queue->_head == NO_HEAD)
    {
        queue->_head = 0;
        queue->_tail = 0;
    }
    else
    {
        queue->_tail++;
    }

    queue->__request_mem_pool[queue->_tail]._perform_func = perform_func;
    memcpy(&(queue->__request_mem_pool[queue->_tail]._data), data, data_size);

    nt_log("NT_PLAT_REQ_QUEUE: PUSH_BACK - h: %d | t: %d", queue->_head, queue->_tail);

    pthread_mutex_unlock(&queue->_lock);
}

// TODO: doesnt work in 'fail' case, will need to implement a real list
void _nt_platform_req_queue_push_front(NTPlatformRequestQueue* queue,
        void (*perform_func)(void* data), void* data, size_t data_size)
{
    pthread_mutex_lock(&queue->_lock);

    if(queue->_head == NO_HEAD)
    {
        queue->_head = 0;
        queue->_tail = 0;
    }
    else
    {
        // fail
        if(queue->_head == 0)
        {
            pthread_mutex_unlock(&queue->_lock);
            return;
        }
        else
            queue->_head--;
    }

    queue->__request_mem_pool[queue->_head]._perform_func = perform_func;
    memcpy(&(queue->__request_mem_pool[queue->_head]._data), data, data_size);

    nt_log("NT_PLAT_REQ_QUEUE: PUSH_BACK - h: %d | t: %d", queue->_head, queue->_tail);

    pthread_mutex_unlock(&queue->_lock);
}

void _nt_platform_request_queue_pop_front(NTPlatformRequestQueue* queue,
        void (**out_perform_func)(void* data), void** out_data)
{
    pthread_mutex_lock(&queue->_lock);

    *out_perform_func = queue->__request_mem_pool[queue->_head]._perform_func;
    *out_data = queue->__request_mem_pool[queue->_head]._data;

    queue->_head++;

    if(queue->_head > queue->_tail)
    {
        queue->_head = NO_HEAD;
        queue->_tail = NO_TAIL;
    }

    nt_log("NT_PLAT_REQ_QUEUE: POP_HEAD - h: %d | t: %d", queue->_head, queue->_tail);

    pthread_mutex_unlock(&queue->_lock);
}

void _nt_platform_request_queue_get_count(NTPlatformRequestQueue* queue,
        size_t* out_request_count)
{
    pthread_mutex_lock(&queue->_lock);

    if(queue->_head == NO_HEAD)
        *out_request_count = 0;
    else
        *out_request_count = queue->_tail - queue->_head + 1;

    pthread_mutex_unlock(&queue->_lock);
}
