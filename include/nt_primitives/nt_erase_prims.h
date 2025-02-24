#ifndef NT_ERASE_PRIMS_H
#define NT_ERASE_PRIMS_H

#define NT_EPRIM_ERASE_ENTIRE_SCREEN_CODE "\e[2J"
// #define NT_EPRIM_ERASE_ENTIRE_SCREEN_CODE "\ec"
#define NT_EPRIM_ERASE_SCROLLBACK_BUFFER_CODE "\e[H\e[3J"
#define NT_EPRIM_ERASE_CURSOR_TO_END_LINE_CODE "\e[0K"
#define NT_EPRIM_ERASE_START_TO_CURSOR_LINE_CODE "\e[1K"
#define NT_EPRIM_ERASE_ENTIRE_LINE_CODE "\e[2K"

void nt_eprim_erase_screen();
void nt_eprim_erase_scrollback_buffer();
void nt_eprim_erase_line();
void nt_eprim_erase_line_start_to_cursor();
void nt_eprim_erase_line_cursor_to_end();

#endif
