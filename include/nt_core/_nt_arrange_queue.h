#ifndef __NT_ARRANGE_QUEUE_H__
#define __NT_ARRANGE_QUEUE_H__

#include <pthread.h>
#include <stdbool.h>

struct NTObject;
typedef struct NTObject NTObject;

/* Used internally by NTDrawEngine. This queue represents requests
 * to the NTDrawEngine. Thread-safe.*/
typedef struct NTArrangeItem
{
    NTObject* _object;
    struct NTArrangeItem* _next;
    bool _arrange_anchored;
} NTArrangeItem;

typedef struct NTArrangeQueue
{
    NTArrangeItem* _head;
    NTArrangeItem* _tail;
    pthread_mutex_t _lock;
    size_t _count;
} NTArrangeQueue;

void _nt_arrange_queue_init(NTArrangeQueue* queue);

void _nt_arrange_queue_push_back(NTArrangeQueue* queue,
        NTObject* object, bool arrange_anchored);

void _nt_arrange_queue_pop_head(NTArrangeQueue* queue,
        NTObject** out_head, bool* out_arrange_anchored);

void _nt_arrange_queue_get_count(NTArrangeQueue* queue,
        size_t* out_count);

#endif // __NT_ARRANGE_QUEUE_H__
