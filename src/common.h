#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>

/* ver.c */
extern const char* dar_version;

/* cmd.c */
extern int dar_show_help;
extern int dar_create;
extern int dar_extract;
extern int dar_test;
extern int dar_info;
extern const char* dar_input;

int dar_cmd(int total, const char* arg);

/* printf.c */
void dar_printf(FILE* out, const char* fmt, ...);

#endif
