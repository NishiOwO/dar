#ifndef __COMINC_H__
#define __COMINC_H__

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

#ifdef HAS_PWD_H
#include <pwd.h>
#endif

#ifdef HAS_GRP_H
#include <grp.h>
#endif

#ifdef HAS_DIRECT_H
#include <direct.h>
#endif

#include <zlib.h>
#include <setjmp.h>

#endif
