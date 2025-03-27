#include "nt_core/platform/nt_platform.h"

#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/eventfd.h>
#include <unistd.h>
#include <assert.h>

#include "nt_core/platform/_nt_platform_request_queue.h"
#include "nt_core/platform/_nt_platform_request_slot.h"
#include "nt_core/platform/_nt_platform_request_slots.h"
#include "nt_core/platform/nt_platform_request.h"
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

static NTPlatformRequestSlots _slots;
static NTPlatformRequestQueue _queue;

/* -------------------------------------------------------------------------- */

void _nt_platform_init()
{
    nt_platform_request_queue_init(&_queue);
    nt_platform_request_slots_init(&_slots);

    pthread_create(&_platform_thread, NULL, _nt_platform_thread_func, NULL);
    nt_lock_init(&_platform_thread_lock, false);
}

void _nt_platform_destroy()
{
    _nt_platform_thread_join();

    nt_platform_request_queue_destroy(&_queue);
    nt_platform_request_slots_destroy(&_slots);

    nt_lock_destroy(&_platform_thread_lock);
}

void nt_platform_execute(NTPlatformRequest* request)
{
    // If current thread is platform thread, execute immediately
    if(pthread_self() == _platform_thread) 
        request->_perform_func(request->_data);
    else // execute later on NTPlatform thread
    {
        nt_platform_request_queue_push_back(&_queue, request);

        nt_log("Adding request");
        nt_lock_unlock(&_platform_thread_lock);
    }

}

NTPlatformRequestSlot* nt_platform_designate_slot()
{
    return nt_platform_request_slots_get_unoccupied(&_slots);
}

void nt_platform_write_to_slot(const NTPlatformRequest* request, NTPlatformRequestSlot* slot)
{
    if(slot == NULL) return;

    nt_platform_request_slot_write(slot, request);

    nt_lock_unlock(&_platform_thread_lock);
}

void nt_platform_depose_slot(NTPlatformRequestSlot* slot)
{
    nt_platform_request_slot_depose(slot);
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
    NTPlatformRequest req;
    bool occupied, empty;
    nt_platform_request_slot_is_occupied(slot, &occupied);
    nt_platform_request_slot_is_empty(slot, &empty);

    if(occupied && !empty)
    {
        nt_platform_request_slot_get_request_copy(slot, &req);
        req._perform_func(req._data);
    }
}

static void _process_async_slots()
{
    size_t i;

    struct NTPlatformRequestSlot* curr_slot;
    for(i = 0; i < NT_PLATFORM_MAX_ASYNC_SLOTS; i++)
    {
        curr_slot = nt_platform_request_slots_get_slot_at(&_slots, i);
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
            // _process_async_slots();
            nt_platform_request_queue_get_count(&_queue, &req_count);
            if(req_count == 0) break;

            nt_platform_request_queue_get_head(&_queue, &req);
            nt_log("Processing request. Current req count: %ld", req_count);

            req->_perform_func(req->_data);

            nt_platform_request_queue_pop_front(&_queue);
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
