#ifndef _NT_SCREEN_H_
#define _NT_SCREEN_H_

void nt_screen_init();
void nt_screen_destruct();

void nt_screen_erase_screen();
void nt_screen_erase_scrollback_buffer();
void nt_screen_erase_line();

void nt_screen_enable_alternate_buffer();
void nt_screen_disable_alternate_buffer();

#endif // _NT_SCREEN_H_
