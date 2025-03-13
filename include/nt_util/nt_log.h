#ifndef _NT_LOG_H_
#define _NT_LOG_H_

void nt_log_init(char* log_filepath);
void nt_log(const char* format, ...);
void nt_log_destruct();

#endif // _NT_LOG_H_
