#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>

#ifdef __STDC_VERSION__
#if __STDC_VERSION__ >= 199901L
#define HAS_C99
#endif
#endif

#ifdef HAS_C99
#include <stdint.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

#undef HAS_C99
#else
#ifdef _MSC_VER
typedef unsigned __int8  u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;

typedef __int8  i8;
typedef __int16 i16;
typedef __int32 i32;
typedef __int64 i64;
#else
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

typedef signed char      i8;
typedef signed short     i16;
typedef signed int       i32;
typedef signed long long i64;
#endif
#endif

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
