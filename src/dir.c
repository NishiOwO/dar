#include "common.h"

#ifdef HAS_DIRENT_H

#elif defined(HAS_WINDOWS_H)

#endif

#ifdef HAS_SYS_STAT_H
int dar_is_dir(const char* path) {
	struct stat s;
	if(stat(path, &s) == 0) {
		return S_ISDIR(s.st_mode) ? 1 : 0;
	}
	return 0;
}
#elif defined(HAS_WINDOWS_H)
int dar_is_dir(const char* path) {
	DWORD dw = GetFileAttributes(path);
	if(dw != INVALID_FILE_ATTRIBUTES) {
		return (dw & FILE_ATTRIBUTE_DIRECTORY) ? 1 : 0;
	}
	return 0;
}
#endif
