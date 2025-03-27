#ifndef _NT_DISPLAY_H_
#define _NT_DISPLAY_H_

#include <stddef.h>

#include "nt_core/display/nt_display_cell.h"
#include "nt_shared/nt_shared.h"

struct NTObject;
typedef struct NTObject NTObject;

struct NTPane;
typedef struct NTPane NTPane;

// TODO: encapsulate
/* The _display_buffer is a global 2D array of NTDisplayCell that acts as a
 * staging area for rendering. Individual NTPanes write their content
 * into this buffer, and once all the panes have updated it, the entire
 * buffer is rendered to the terminal screen. This centralized approach 
 * helps compose multiple panels into a single cohesive output(respecting
 * each pane's layering). It also stores data about which cell of the
 * terminal is occupied by which pane. */
extern NTDisplayCell _display_buffer[NT_DISPLAY_MAX_HEIGHT][NT_DISPLAY_MAX_WIDTH];

void _nt_display_init();
void _nt_display_destroy();

/* This function draws NTPanes to _display_buffer at the appropriate coordinates
 * (calculated by nt_bounds_calculate_abs_bounds). It is in an internal function
 * used only in NTPane's internal logic.
 *
 * This function alters the internal state of the NTDisplay buffer. Thus,
 * it must be called from the context of the NTPlatform thread to avoid any
 * race conditions. */
void _nt_display_draw_pane_to_buffer(NTPane* pane);

void nt_display_set_root(NTObject* object);
NTObject* nt_display_get_root();

size_t nt_display_get_width();
size_t nt_display_get_height();

#endif // _NT_DISPLAY_H_
