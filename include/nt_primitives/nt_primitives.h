#ifndef NT_PRIMITIVES_H
#define NT_PRIMITIVES_H

#define CODE_BUFF_LEN 15

#include <string.h>

extern char code_buff[CODE_BUFF_LEN];

#define WRITE_CODE write(STDOUT_FILENO, code_buff, strlen(code_buff))

#endif
