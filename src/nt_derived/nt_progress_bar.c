#include "nt_derived/nt_progress_bar.h"
#include <math.h>

static void _object_arrange_func(NTObject* progress_bar);

static void _object_calculate_req_size_func(const NTObject* progress_bar,
        size_t* out_width, size_t* out_height);

static NTDisplayCell _window_get_content_at_func(const NTWindow* progress_bar,
        size_t x, size_t y);

// -----------------------------------------------------------------------------------

void nt_progress_bar_init(NTProgressBar* progress_bar,
    NTOrientation orientation,
    nt_color completed_color,
    nt_color uncompleted_color)
{
    nt_window_init((NTWindow*)progress_bar, _object_calculate_req_size_func, _object_arrange_func, _window_get_content_at_func);

    progress_bar->_orientation = orientation;
    progress_bar->_completed_color = completed_color;
    progress_bar->_uncompleted_color = uncompleted_color;
    progress_bar->_progress = 0;
    progress_bar->_completed_threshold = 0;
}

void nt_progress_bar_set_progress(NTProgressBar* progress_bar, double new_progress)
{
    progress_bar->_progress = new_progress;
    // TODO - redraw
}

double nt_progress_bar_get_progress(NTProgressBar* progress_bar)
{
    return progress_bar->_progress;
}

nt_color nt_progress_bar_get_completed_color(const NTProgressBar* progress_bar)
{
    return progress_bar->_completed_color;
}

nt_color nt_progress_bar_get_uncompleted_color(const NTProgressBar* progress_bar)
{
    return progress_bar->_uncompleted_color;
}

void nt_solid_color_block_set_completed_color(NTProgressBar* progress_bar, nt_color new_completed_color)
{
    progress_bar->_completed_color = new_completed_color;
    // TODO - redraw
}

void nt_solid_color_block_set_uncompleted_color(NTProgressBar* progress_bar, nt_color new_uncompleted_color)
{
    progress_bar->_uncompleted_color = new_uncompleted_color;
    // TODO - redraw
}

static void _object_arrange_func(NTObject* progress_bar)
{
    NTProgressBar* _progress_bar = (NTProgressBar*)progress_bar;

    if(_progress_bar->_orientation == NT_ORIENTATION_HORIZONTAL)
    {
        size_t width = nt_bounds_calculate_width(&progress_bar->_bounds);
        _progress_bar->_completed_threshold = (size_t)round((double)width * _progress_bar->_progress);
    }
    else
    {
        size_t height = nt_bounds_calculate_height(&progress_bar->_bounds);
        _progress_bar->_completed_threshold = (size_t)round((double)height * _progress_bar->_progress);
    }

}

static void _object_calculate_req_size_func(const NTObject* progress_bar,
        size_t* out_width, size_t* out_height)
{
    *out_width = 0;
    *out_height = 0;
}

static NTDisplayCell _window_get_content_at_func(const NTWindow* progress_bar,
        size_t x, size_t y)
{
    NTProgressBar* _progress_bar = (NTProgressBar*)progress_bar;

    nt_color bg_color;
    if(_progress_bar->_orientation == NT_ORIENTATION_HORIZONTAL)
    {
        bg_color = (x <= _progress_bar->_completed_threshold) ? _progress_bar->_completed_color : _progress_bar->_uncompleted_color;
    }
    else
    {
        bg_color = (y <= _progress_bar->_completed_threshold) ? _progress_bar->_completed_color : _progress_bar->_uncompleted_color;
    }

    NTDisplayCell display_cell;

    nt_display_cell_init_empty(&display_cell, bg_color);

    return display_cell;
}
