#include "nt_core/nt_draw_engine.h"
#include "nt_component/base/nt_object.h"
#include "nt_core/_nt_arrange_queue.h"
#include "nt_env/base/nt_cursor.h"
#include "nt_env/nt_display.h"
#include "nt_util/nt_log.h"
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>

#define USE_DRAW_THREAD

static pthread_t _draw_thread;
static sem_t _draw_thread_lock;
void* _draw_thread_func(void* data);

static NTArrangeQueue _arrange_queue;

void _nt_draw_engine_init()
{
#ifdef USE_DRAW_THREAD

    sem_init(&_draw_thread_lock, 0, 0);
    _nt_arrange_queue_init(&_arrange_queue);

    pthread_create(&_draw_thread, NULL, _draw_thread_func, NULL);

#endif // USE_DRAW_THREAD
}

void _nt_draw_engine_destruct()
{
#ifdef USE_DRAW_THREAD
    sem_destroy(&_draw_thread_lock);
#endif // USE_DRAW_THREAD

    // TODO 
    // pthread_join(_draw_thread, NULL);
}

#define BUFF_SIZE 2000
static char _buffer[BUFF_SIZE];
#define ENABLE_BUFFERING() setvbuf(stdout, _buffer, _IOFBF, BUFF_SIZE)
#define DISABLE_BUFFERING() setvbuf(stdout, NULL, _IONBF, 0)

void _draw_display_buffer()
{
    size_t width = nt_display_get_width();
    size_t height = nt_display_get_height();

    size_t i, j;

    NTDisplayCell* curr_display_cell;
    ENABLE_BUFFERING();
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            curr_display_cell = &_display_buffer[i][j];

            nt_style_set(curr_display_cell->_style);
            nt_color_set_fg(curr_display_cell->_fg_color);
            nt_color_set_bg(curr_display_cell->_bg_color);
            nt_cursor_abs_move_to_xy(j, i);
            putchar(curr_display_cell->_content);
        }
    }

    fflush(stdout);
    DISABLE_BUFFERING();
}

void nt_draw_engine_draw_object_tree(NTObject* root_object, bool arrange_anchored)
{
#ifdef USE_DRAW_THREAD

    _nt_arrange_queue_push_back(&_arrange_queue, root_object, arrange_anchored);
    sem_post(&_draw_thread_lock);

#else

    _nt_object_arrange(root_object, arrange_anchored);

    _nt_object_display(nt_display_get_root());

    _draw_display_buffer();

#endif // USE_DRAW_THREAD
}

void* _draw_thread_func(void* data)
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGWINCH);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    NTObject* curr_obj = NULL;
    bool curr_arr_anchored = false;
    size_t curr_count;
    while(1)
    {
        sem_wait(&_draw_thread_lock);

        // Object for drawing arrived

        _nt_arrange_queue_pop_head(&_arrange_queue, &curr_obj, &curr_arr_anchored);

        _nt_arrange_queue_get_count(&_arrange_queue, &curr_count);
        if(curr_count > 0)
            nt_log("NT_DRAW_ENGINE: Object: %p arrives for drawing. (S)", curr_obj);
        else
        {
            nt_log("NT_DRAW_ENGINE: Object: %p arrives for drawing. (D)", curr_obj);
            _nt_object_arrange(curr_obj, curr_arr_anchored);

            _nt_object_display(nt_display_get_root());

            _draw_display_buffer();
        }
    }

    return NULL;
}
