#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef __STDC_VERSION__
#if __STDC_VERSION__ >= 199901L
#define HAS_C99
#endif
#endif

#ifdef HAS_C99
#include <stdint.h>

typedef uint8_t	 u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t	i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

#undef HAS_C99
#else
#ifdef _MSC_VER
typedef unsigned __int8	 u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;

typedef __int8	i8;
typedef __int16 i16;
typedef __int32 i32;
typedef __int64 i64;
#else
typedef unsigned char	   u8;
typedef unsigned short	   u16;
typedef unsigned int	   u32;
typedef unsigned long long u64;

typedef signed char	 i8;
typedef signed short	 i16;
typedef signed int	 i32;
typedef signed long long i64;
#endif
#endif

#if defined(__WATCOMC__) || defined(__unix__)
#define HAS_DIRENT_H
#define HAS_SYS_STAT_H
#endif

#ifdef _WIN32
#define HAS_WINDOWS_H
#endif

#include "stb_ds.h"

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef HAS_WINDOWS_H
#include <windows.h>
#endif

#ifdef HAS_SYS_STAT_H
#include <sys/stat.h>
#endif

#ifdef HAS_DIRENT_H
#include <dirent.h>
#endif

enum dar_chunktypes {
	DAR_CHUNK_FILE = 0,
	DAR_CHUNK_DIRECTORY,
	DAR_CHUNK_END = 0xff
};

#pragma pack(1)
typedef struct dar_header {
	u8   type;
	u16  mode;
	u32  size;
	char user[128];
	u32  uid;
	char group[128];
	u32  gid;
} dar_header_t;
#pragma pack()

/* dar.c */
extern FILE* dar_io;

/* ver.c */
extern const char* dar_version;

/* cmd.c */
extern int	    dar_show_help;
extern int	    dar_create;
extern int	    dar_extract;
extern int	    dar_test;
extern int	    dar_info;
extern const char*  dar_input;
extern const char** dar_files;

int dar_cmd(int total, const char* arg);

/* printf.c */
void dar_printf(FILE* out, const char* fmt, ...);

/* chunk.c */
void dar_write(const char* path);

/* dir.c */
int dar_is_dir(const char* path);

/* commands */
int dar_cmd_create(void);
int dar_cmd_extract(void);
int dar_cmd_test(void);
int dar_cmd_info(void);

#endif
