#include <assert.h>
#include <math.h>

#include "nt_derived/nt_progress_bar.h"
#include "nt_core/nt_color.h"
#include "nt_shared/nt_display_cell.h"

void nt_progress_bar_init(struct NTProgressBar* progress_bar,
        NTProgressBarOrientation orientation,
        size_t completed_color_code,
        size_t uncompleted_color_code)
{
    assert(progress_bar != NULL);

     nt_window_init((struct NTWindow*)progress_bar,
             _nt_progress_bar_calculate_required_size_func,
             _nt_progress_bar_draw_window_func,
             _nt_progress_bar_get_content_at_func,
             NT_DRAW_ENGINE_HIGH_DRAW_PRIORITY);

     progress_bar->_orientation = orientation;
     progress_bar->_completed_color_code = completed_color_code;
     progress_bar->_uncompleted_color_code = uncompleted_color_code;
     progress_bar->_progress = 0;
}

void nt_progress_bar_set_progress(struct NTProgressBar* progress_bar, double new_progress)
{
    assert(progress_bar != NULL);

    progress_bar->_progress = new_progress;

    // TODO - redraw?
}

double nt_progress_bar_get_progress(struct NTProgressBar* progress_bar)
{
    assert(progress_bar != NULL);

    return progress_bar->_progress;
}

void _nt_progress_bar_calculate_required_size_func(struct NTWindow* progress_bar, size_t* required_x, size_t* required_y)
{
    assert(progress_bar != NULL);
    assert(required_x != NULL);
    assert(required_y != NULL);

    *required_x = 0;
    *required_y = 0;
}

void _nt_progress_bar_get_content_at_func(struct NTWindow* progress_bar, size_t x, size_t y, struct NTDisplayCell* display_cell_buff)
{
    assert(progress_bar != NULL);
    assert(display_cell_buff != NULL);

    struct NTProgressBar* _progress_bar = (struct NTProgressBar*)progress_bar;
    struct NTObject* __progress_bar = (struct NTObject*)progress_bar;
    double progress = _progress_bar->_progress;

    size_t progress_bar_height = nt_object_calculate_height(__progress_bar);
    size_t progress_bar_width = nt_object_calculate_width(__progress_bar);

    assert(x < progress_bar_width);
    assert(y < progress_bar_height);

    size_t progress_bar_length, progress_bar_pos; // TODO -- rename?
    if (_progress_bar->_orientation == NT_PROGRESS_BAR_HORIZONTAL_ORIENTATION)
    { 
        progress_bar_length = progress_bar_width;
        progress_bar_pos = x;
    }
    else
    {
        progress_bar_length = progress_bar_height;
        progress_bar_pos = y;
    }

    size_t completed_length = (size_t)(round((double)progress_bar_length * progress) / 100);

    display_cell_buff->bg_color_code = ((progress_bar_pos < completed_length) ? _progress_bar->_completed_color_code : _progress_bar->_uncompleted_color_code);
    display_cell_buff->fg_color_code = NT_COLOR_DEFAULT;
    display_cell_buff->content = ' ';
}

void _nt_progress_bar_draw_window_func(struct NTWindow* progress_bar, size_t width, size_t height)
{
    assert(progress_bar != NULL);

    return;
}
