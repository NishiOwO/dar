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

#include "machdep.h"
#include "cominc.h"

enum dar_chunktypes {
	DAR_CHUNK_FILE = 0,
	DAR_CHUNK_DIRECTORY,
	DAR_CHUNK_END = 0xff
};

#pragma pack(1)
typedef struct dar_header {
	u8   type;
	char name[256];
	u16  mode;
	char user[128];
	u16  uid;
	char group[128];
	u16  gid;
	u32  size; /* this is size after compression */
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
extern int	    dar_quality;

int dar_cmd(int total, const char* arg);

/* printf.c */
void dar_printf(FILE* out, const char* fmt, ...);

/* chunk.c */
void dar_write(const char* path);
void dar_read(dar_header_t* hdr);

/* io.c */
int   dar_get_info(const char* path, dar_header_t* hdr);
void* dar_opendir(const char* path);
void  dar_closedir(void* handle);
char* dar_readdir(void* handle);

/* commands */
int dar_cmd_create(void);
int dar_cmd_extract(void);
int dar_cmd_test(void);
int dar_cmd_info(void);

#ifdef ENDIAN_IMPLEMENTATION
#define DAR_BE(type) \
	type dar_##type##be(type n) { \
		u16 s = 1; \
		if((*(u8*)&s) == 1) { \
			/* little endian */ \
			type r = 0; \
			int  i; \
			for(i = 0; i < sizeof(n); i++) { \
				r = r << 8; \
				r = r | (n & 0xff); \
				n = n >> 8; \
			} \
			return r; \
		} \
		return n; \
	}
#else
#define DAR_BE(type) type dar_##type##be(type n);
#endif

DAR_BE(u32)
DAR_BE(u16)

#endif
