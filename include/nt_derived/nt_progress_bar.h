#ifndef NT_PROGRESS_BAR_H
#define NT_PROGRESS_BAR_H

#include "nt_base/nt_window.h"

typedef enum { NT_PROGRESS_BAR_ORIENTATION_HORIZONTAL, NT_PROGRESS_BAR_ORIENTATION_VERTICAL } NTProgressBarOrientation;

struct NTProgressBar
{
    struct NTWindow _base;

    double _progress;
    NTProgressBarOrientation _orientation;
    size_t _completed_color_code, _uncompleted_color_code;
};

void nt_progress_bar_init(struct NTProgressBar* progress_bar,
        NTProgressBarOrientation orientation,
        size_t completed_color_code,
        size_t uncompleted_color_code);

void nt_progress_bar_set_progress(struct NTProgressBar* progress_bar, double new_progress);
double nt_progress_bar_get_progress(struct NTProgressBar* progress_bar);

void _nt_progress_bar_calculate_required_size_func(struct NTWindow* progress_bar, size_t* required_x, size_t* required_y);
void _nt_progress_bar_get_content_at_func(struct NTWindow* progress_bar, size_t x, size_t y, struct NTDisplayCell* display_cell_buff);
void _nt_progress_bar_draw_window_func(struct NTWindow* progress_bar, size_t width, size_t height);

#endif
