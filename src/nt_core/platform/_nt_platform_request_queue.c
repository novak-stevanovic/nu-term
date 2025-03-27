#include "nt_core/platform/_nt_platform_request_queue.h"

#include <assert.h>
#include "sarena/sarena.h"
#include "nt_core/platform/nt_platform_request.h"

#define ARENA_REGION_CAP (sizeof(struct NTPlatformRequestNode) * 5000)

#define QUEUE_LOCK(queue) pthread_mutex_lock(&queue->_lock)
#define QUEUE_UNLOCK(queue) pthread_mutex_unlock(&queue->_lock)

/* -------------------------------------------------------------------------- */

struct NTPlatformRequestNode
{
    NTPlatformRequest request;
    struct NTPlatformRequestNode* next;
};

static struct NTPlatformRequestNode* _request_node_alloc(NTPlatformRequestQueue*
        queue, NTPlatformRequest* request);

/* -------------------------------------------------------------------------- */

void nt_platform_request_queue_init(NTPlatformRequestQueue* queue)
{
    queue->_head = NULL;
    queue->_tail = NULL;
    queue->_count = 0;

    sa_err err;
    queue->_arena = sarena_create(ARENA_REGION_CAP, &err);
    assert(err == SA_SUCCESS);

    pthread_mutex_init(&queue->_lock, NULL);
}

void nt_platform_request_queue_destroy(NTPlatformRequestQueue* queue)
{
    queue->_head = NULL;
    queue->_tail = NULL;
    queue->_count = 0;

    pthread_mutex_destroy(&queue->_lock);

    sarena_destroy(queue->_arena);
}

void nt_platform_request_queue_push_back(NTPlatformRequestQueue* queue,
        NTPlatformRequest* request)
{
    QUEUE_LOCK(queue);

    struct NTPlatformRequestNode* new = _request_node_alloc(queue, request);

    if(queue->_head == NULL)
    {
        queue->_head = new;
        queue->_tail = new;
    }
    else
    {
        queue->_tail->next = new;
        queue->_tail = new;
    }

    queue->_count++;

    QUEUE_UNLOCK(queue);
}

void nt_platform_request_queue_get_head(NTPlatformRequestQueue* queue,
        NTPlatformRequest** out_request)
{
    QUEUE_LOCK(queue);

    NTPlatformRequest* ret_val;
    if(queue->_count == 0)
        ret_val = NULL;
    else
    {
        ret_val = &queue->_head->request;
    }

    if(out_request != NULL) *out_request = ret_val;

    QUEUE_UNLOCK(queue);
}

void nt_platform_request_queue_pop_front(NTPlatformRequestQueue* queue)
{
    QUEUE_LOCK(queue);

    if(queue->_head == queue->_tail)
    {
        queue->_head = NULL;
        queue->_tail = NULL;

        sarena_rewind(queue->_arena);
    }
    else
    {
        queue->_head = queue->_head->next;
    }

    queue->_count--;

    QUEUE_UNLOCK(queue);
}

void nt_platform_request_queue_get_count(NTPlatformRequestQueue* queue,
        size_t *out_count)
{
    QUEUE_LOCK(queue);

    if(out_count != NULL) *out_count = queue->_count;

    QUEUE_UNLOCK(queue);
}

/* -------------------------------------------------------------------------- */

static struct NTPlatformRequestNode* _request_node_alloc(NTPlatformRequestQueue*
        queue, NTPlatformRequest* request)
{
    sa_err err;

    struct NTPlatformRequestNode* new = sarena_malloc(queue->_arena,
            sizeof(struct NTPlatformRequestNode), &err);

    assert(err == SA_SUCCESS);

    // Copy
    new->request = *request;
    new->next = NULL;

    return new;
}
