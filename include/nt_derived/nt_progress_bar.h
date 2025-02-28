#ifndef NT_PROGRESS_BAR_H
#define NT_PROGRESS_BAR_H

#include "nt_base/nt_window.h"

typedef struct NTProgressBar
{
    NTWindow _base;
    
    double _progress;
    nt_color _completed_color;
    nt_color _uncompleted_color;
    size_t _completed_threshold;
    NTOrientation _orientation;
} NTProgressBar;

void nt_progress_bar_init(NTProgressBar* progress_bar,
    NTOrientation orientation,
    nt_color completed_color,
    nt_color uncompleted_color);

void nt_progress_bar_set_progress(NTProgressBar* progress_bar, double new_progress);
double nt_progress_bar_get_progress(NTProgressBar* progress_bar);

nt_color nt_progress_bar_get_completed_color(const NTProgressBar* progress_bar);
nt_color nt_progress_bar_get_uncompleted_color(const NTProgressBar* progress_bar);

void nt_solid_color_block_set_completed_color(NTProgressBar* progress_bar, nt_color new_completed_color);
void nt_solid_color_block_set_uncompleted_color(NTProgressBar* progress_bar, nt_color new_uncompleted_color);

#endif
