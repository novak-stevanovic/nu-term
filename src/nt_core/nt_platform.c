#include "nt_core/nt_platform.h"
#include "nt_core/_nt_platform_request_queue.h"
#include "nt_util/nt_log.h"
#include <bits/types/sigset_t.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/eventfd.h>
#include <unistd.h>

/* -------------------------------------------------------------------------- */

// NTPlatform thread

static pthread_t _platform_thread = 0;
static int _signal_efd = 0;
static bool _program_end = false;

static void* _nt_platform_thread_func(void* data); // Function to create thread

static void _nt_platform_thread_init(); // Called from NTPlatform thread
static void _nt_platform_thread_join(); // Called from main thread
                                        //
static void _nt_platform_thread_wake(); // Called from main thread
static void _nt_platform_thread_wait(); // Called from NTPlatform thread

/* -------------------------------------------------------------------------- */

static NTPlatformRequestQueue _request_queue;

void _nt_platform_init()
{
    _signal_efd = eventfd(0, 0); 
    _nt_platform_req_queue_init(&_request_queue);

    pthread_create(&_platform_thread, NULL, _nt_platform_thread_func, NULL);
}

void _nt_platform_destroy()
{
    _nt_platform_thread_join();

    _nt_platform_req_queue_destroy(&_request_queue);

}

void nt_platform_execute(void (*request_func)(void* data),
        void* data, size_t data_size)
{
    // If current thread is platform thread, execute immediately
    if(pthread_self() == _platform_thread) 
        request_func(data);
    else // execute later on NTPlatform thread
    {
        _nt_platform_req_queue_push_back(&_request_queue,
                request_func, data, data_size);

        _nt_platform_thread_wake();
    }

}

// TODO - think about what happens if called from NTPlatform thread.
// Remember to rethink push_front() func as it doesn't work if the
// first req hasn't been processed.
void nt_platform_execute_first(void (*request_func)(void* data),
        void* data, size_t data_size)
{
        _nt_platform_req_queue_push_front(&_request_queue,
                request_func, data, data_size);

        _nt_platform_thread_wake();
}

/* -------------------------------------------------------------------------- */

static void _nt_platform_thread_init()
{
    _platform_thread = pthread_self();
    nt_log("NT_PLATFORM: THREAD STARTED %lu (PID)", _platform_thread);

    // Block SIGWINCH
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGWINCH);
    pthread_sigmask(SIG_BLOCK, &set, NULL);
}

static void* _nt_platform_thread_func(void* data)
{
    _nt_platform_thread_init();

    void (*req_perform_func)(void *);
    void* req_data;
    size_t req_count;
    while(!_program_end)
    {
        _nt_platform_thread_wait();

        while(true)
        {
            _nt_platform_request_queue_get_count(&_request_queue, &req_count);
            nt_log("NT_PLATFORM: req_count: %d", req_count);
            if(req_count == 0) break;
            
            _nt_platform_request_queue_pop_front(&_request_queue,
                    &req_perform_func, &req_data);

            if(req_perform_func) req_perform_func(req_data);
        }
    }

    return NULL;
}

static void _nt_platform_thread_wake()
{
    uint64_t signal_value = 1;
    write(_signal_efd, &signal_value, sizeof(uint64_t));
}

static void _nt_platform_thread_wait()
{
    uint64_t signal_value;
    read(_signal_efd, &signal_value, sizeof(uint64_t));
}

static void _nt_platform_thread_join()
{
    _program_end = true;
    nt_platform_execute(NULL, NULL, 0);
    close(_signal_efd);
    pthread_join(_platform_thread, NULL);
}
