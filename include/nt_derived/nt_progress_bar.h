#ifndef NT_PROGRESS_BAR_H
#define NT_PROGRESS_BAR_H

#include "nt_base/nt_simple_window.h"

typedef enum { NT_PROGRESS_BAR_ORIENTATION_HORIZONTAL, NT_PROGRESS_BAR_ORIENTATION_VERTICAL } NTProgressBarOrientation;

struct NTProgressBar
{
    struct NTSimpleWindow _base;

    double _progress;
    NTProgressBarOrientation _orientation;
    size_t _completed_color_code, _uncompleted_color_code;
};

void nt_progress_bar_init(struct NTProgressBar* progress_bar,
        NTProgressBarOrientation orientation,
        size_t completed_color_code,
        size_t uncompleted_color_code,
        NTDrawEngineDrawPriority draw_priority);

void nt_progress_bar_set_progress(struct NTProgressBar* progress_bar, double new_progress);
double nt_progress_bar_get_progress(struct NTProgressBar* progress_bar);

#endif

