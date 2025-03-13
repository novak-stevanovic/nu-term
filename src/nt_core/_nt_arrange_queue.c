#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "nt_core/_nt_arrange_queue.h"
#include "pthread.h"

static NTArrangeItem* _arrange_item_alloc(NTObject* object, bool arrange_anchored);

void _nt_arrange_queue_init(NTArrangeQueue* queue)
{
    queue->_head = NULL;
    queue->_tail = NULL;
    queue->_count = 0;
    pthread_mutex_init(&queue->_lock, NULL);
}

void _nt_arrange_queue_push_back(NTArrangeQueue* queue,
        NTObject* object, bool arrange_anchored)
{
    pthread_mutex_lock(&queue->_lock);

    NTArrangeItem* new = _arrange_item_alloc(object, arrange_anchored);
    if(new == NULL)
    {
        pthread_mutex_unlock(&queue->_lock);
        return;
    }

    if(queue->_head != NULL)
    {
        queue->_tail->_next = new;
        queue->_tail = new;
    }
    else
    {
        queue->_head = new;
        queue->_tail = new;
    }

    queue->_count++;

    pthread_mutex_unlock(&queue->_lock);
}

void _nt_arrange_queue_pop_head(NTArrangeQueue* queue,
        NTObject** out_head, bool* out_arrange_anchored)
{
    pthread_mutex_lock(&queue->_lock);

    NTArrangeItem* head = queue->_head;

    if(head->_next != NULL)
    {
        queue->_head = head->_next;
    }
    else
    {
        queue->_head = NULL;
        queue->_tail = NULL;
    }

    *out_head = head->_object;
    *out_arrange_anchored = head->_arrange_anchored;
    free(head);
    queue->_count--;

    pthread_mutex_unlock(&queue->_lock);
}

void _nt_arrange_queue_get_count(NTArrangeQueue* queue,
        size_t* out_count)
{
    pthread_mutex_lock(&queue->_lock);

    *out_count = queue->_count;

    pthread_mutex_unlock(&queue->_lock);
}

static NTArrangeItem* _arrange_item_alloc(NTObject* object, bool arrange_anchored)
{
    NTArrangeItem* new = (NTArrangeItem*)malloc(sizeof(NTArrangeItem));

    if(new == NULL) return NULL;

    new->_object = object;
    new->_next = NULL;
    new->_arrange_anchored = arrange_anchored;

    return new;
}
