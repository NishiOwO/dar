#ifndef __MACHDEP_H__
#define __MACHDEP_H__

#if defined(__WATCOMC__) || defined(__unix__)
#define HAS_DIRENT_H
#define HAS_SYS_STAT_H
#endif

#ifdef __unix__
#define HAS_PWD_H
#define HAS_GRP_H
#endif

#ifdef _WIN32
#define HAS_WINDOWS_H
#define HAS_DIRECT_H
#endif

#ifdef _WIN32
#define DAR_PATH_SEPARATOR "\\"
#else
#define DAR_PATH_SEPARATOR "/"
#endif

#endif
