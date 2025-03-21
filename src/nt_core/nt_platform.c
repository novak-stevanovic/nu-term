#include "nt_core/nt_platform.h"

#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/eventfd.h>
#include <unistd.h>
#include <assert.h>

#include "nt_core/_nt_platform_request_queue.h"
#include "nt_core/nt_platform_request.h"
#include "nt_shared/nt_lock.h"
#include "nt_util/nt_log.h"

/* -------------------------------------------------------------------------- */

// NTPlatform thread

static pthread_t _platform_thread = 0;
static bool _program_end = false;
static NTLock _platform_thread_lock;

static void* _nt_platform_thread_func(void* data); // Function to create thread

static void _nt_platform_thread_init(); // Called from NTPlatform thread
static void _nt_platform_thread_join(); // Called from main thread

static void _process_async_slots(); // Called from NTPlatform thread

/* -------------------------------------------------------------------------- */

static NTPlatformRequestQueue _request_queue;

struct NTPlatformRequestSlot
{
    NTLock _lock;
    bool empty;
    NTPlatformRequest request;
    bool occupied;
};

static struct NTPlatformRequestSlot
_async_slots[NT_PLATFORM_MAX_ASYNC_SLOTS] = {0};

static ssize_t _get_first_empty_async_slot();

/* -------------------------------------------------------------------------- */

void _nt_platform_init()
{
    nt_platform_request_queue_init(&_request_queue);

    pthread_create(&_platform_thread, NULL, _nt_platform_thread_func, NULL);
    nt_lock_init(&_platform_thread_lock, false);
}

void _nt_platform_destroy()
{
    _nt_platform_thread_join();

    nt_platform_request_queue_destroy(&_request_queue);

    nt_lock_destroy(&_platform_thread_lock);
}

void nt_platform_execute(NTPlatformRequest* request)
{
    // If current thread is platform thread, execute immediately
    if(pthread_self() == _platform_thread) 
        request->_perform_func(request->_data);
    else // execute later on NTPlatform thread
    {
        nt_platform_request_queue_push_back(&_request_queue, request);

        nt_log("Adding request");
        nt_lock_unlock(&_platform_thread_lock);
    }

}

static ssize_t _get_first_empty_async_slot()
{
    size_t i;
    for(i = 0; i < NT_PLATFORM_MAX_ASYNC_SLOTS; i++)
    {
        if(_async_slots[i].occupied == false)
            return i;
    }

    return -1;
}

size_t nt_platform_designate_slot()
{
    size_t slot_idx = _get_first_empty_async_slot();

    assert(slot_idx != -1);

    _async_slots[slot_idx].occupied = true;
    nt_lock_init(&_async_slots[slot_idx]._lock, true);
    return slot_idx;
}

void nt_platform_write_to_slot(const NTPlatformRequest* request, size_t slot_idx)
{
    assert(slot_idx <= NT_PLATFORM_MAX_ASYNC_SLOTS);

    // nt_lock_lock(&_async_slots[slot_idx]._lock);

    nt_log("Written to slot: %ld", slot_idx);
    _async_slots[slot_idx].request = *request;
    _async_slots[slot_idx].empty = false;

    // nt_lock_unlock(&_async_slots[slot_idx]._lock);

    nt_lock_unlock(&_platform_thread_lock);
}

void nt_platform_depose_slot(size_t slot_idx)
{
    assert(slot_idx <= NT_PLATFORM_MAX_ASYNC_SLOTS);

    _async_slots[slot_idx].occupied = false;
}

/* -------------------------------------------------------------------------- */

static void _nt_platform_thread_init()
{
    nt_log("NT_PLATFORM: THREAD STARTED %lu (PID)", _platform_thread);

    // Block SIGWINCH
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGWINCH);
    pthread_sigmask(SIG_BLOCK, &set, NULL);
}

static void _process_async_slot(struct NTPlatformRequestSlot* slot)
{
    if(slot->occupied == true && slot->empty == false)
    {
        nt_lock_lock(&slot->_lock);
        nt_log("Processing active slot: %p", slot);
        slot->request._perform_func(slot->request._data);
        slot->empty = true;
        nt_lock_unlock(&slot->_lock);
    }
}

static void _process_async_slots()
{
    size_t i;

    struct NTPlatformRequestSlot* curr_slot;
    for(i = 0; i < NT_PLATFORM_MAX_ASYNC_SLOTS; i++)
    {
        curr_slot = &_async_slots[i];
        _process_async_slot(curr_slot);
    }
}

static void* _nt_platform_thread_func(void* data)
{
    _nt_platform_thread_init();

    while(!_program_end)
    {
        nt_lock_lock(&_platform_thread_lock);
        
        NTPlatformRequest* req;
        size_t req_count;
        while(true)
        {
            _process_async_slots();
            nt_platform_request_queue_get_count(&_request_queue, &req_count);
            if(req_count == 0) break;

            nt_platform_request_queue_get_head(&_request_queue, &req);
            nt_log("Processing request. Current req count: %ld", req_count);

            req->_perform_func(req->_data);

            nt_platform_request_queue_pop_front(&_request_queue);
        }
    }

    return NULL;
}

static void _nt_platform_thread_join()
{
    _program_end = true;
    nt_lock_unlock(&_platform_thread_lock);
    pthread_join(_platform_thread, NULL);
}
