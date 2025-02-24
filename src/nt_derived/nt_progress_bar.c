#include "nt_derived/nt_progress_bar.h"

#include <math.h>

#include "nt_derived/nt_progress_bar.h"
#include "nt_core/nt_color.h"
#include "nt_misc.h"
#include "nt_shared/nt_display_cell.h"

static struct NTDisplayCell _nt_progress_bar_get_content_at_func(struct NTWindow* progress_bar, size_t x, size_t y);

void nt_progress_bar_init(struct NTProgressBar* progress_bar,
        NTProgressBarOrientation orientation,
        size_t completed_color_code,
        size_t uncompleted_color_code,
        NTDrawEngineDrawPriority draw_priority)
{
    nt_simple_window_init((struct NTSimpleWindow*)progress_bar, _nt_progress_bar_get_content_at_func, draw_priority);

     progress_bar->_orientation = orientation;
     progress_bar->_completed_color_code = completed_color_code;
     progress_bar->_uncompleted_color_code = uncompleted_color_code;
     progress_bar->_progress = 0;
}

void nt_progress_bar_set_progress(struct NTProgressBar* progress_bar, double new_progress)
{
    progress_bar->_progress = nt_misc_conform_val(0, new_progress, 100);
    // TODO - redraw?
}

double nt_progress_bar_get_progress(struct NTProgressBar* progress_bar)
{
    return progress_bar->_progress;
}

static struct NTDisplayCell _nt_progress_bar_get_content_at_func(struct NTWindow* progress_bar, size_t x, size_t y)
{
    struct NTProgressBar* _progress_bar = (struct NTProgressBar*)progress_bar;
    struct NTObject* __progress_bar = (struct NTObject*)progress_bar;
    double progress = _progress_bar->_progress;

    size_t progress_bar_height = nt_object_calculate_height(__progress_bar);
    size_t progress_bar_width = nt_object_calculate_width(__progress_bar);

    size_t progress_bar_length, progress_bar_pos; // TODO -- rename?
    if (_progress_bar->_orientation == NT_PROGRESS_BAR_ORIENTATION_HORIZONTAL)
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

    struct NTDisplayCell display_cell;
    display_cell.bg_color_code = ((progress_bar_pos < completed_length) ? _progress_bar->_completed_color_code : _progress_bar->_uncompleted_color_code);
    display_cell.fg_color_code = 0;
    display_cell.content = ' ';

    return display_cell;
}

