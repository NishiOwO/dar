#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>

/* ver.c */
extern const char* zar_version;

/* cmd.c */
extern int zar_show_help;

int zar_cmd(const char* arg);

/* printf.c */
void zar_printf(FILE* out, const char* fmt, ...);

#endif
