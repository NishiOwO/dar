#include "common.h"

#ifdef HAS_DIRENT_H
typedef struct dar_dir {
	DIR*  dir;
	char* path;
} dar_dir_t;

void* dar_opendir(const char* path) {
	DIR*	   dir = opendir(path);
	dar_dir_t* d;

	if(dir == NULL) return NULL;

	d	= malloc(sizeof(*d));
	d->dir	= dir;
	d->path = malloc(strlen(path) + 1);
	strcpy(d->path, path);
	return d;
}

char* dar_readdir(void* handle) {
	dar_dir_t* dir = (dar_dir_t*)handle;
	while(1) {
		struct dirent* d = readdir(dir->dir);
		char*	       r;
		if(d == NULL) return NULL;
		if(strcmp(d->d_name, "..") == 0 || strcmp(d->d_name, ".") == 0) continue;

		r    = malloc(strlen(dir->path) + strlen(DAR_PATH_SEPARATOR) + strlen(d->d_name) + 1);
		r[0] = 0;

		strcat(r, dir->path);
		strcat(r, DAR_PATH_SEPARATOR);
		strcat(r, d->d_name);
		return r;
	}
}

void dar_closedir(void* handle) {
	dar_dir_t* dir = (dar_dir_t*)handle;
	closedir(dir->dir);
	free(dir->path);
	free(dir);
}
#elif defined(HAS_WINDOWS_H)

#endif

#if defined(HAS_SYS_STAT_H) && defined(HAS_PWD_H) && defined(HAS_GRP_H)
int dar_get_info(const char* path, dar_header_t* hdr) {
	struct stat s;
	if(stat(path, &s) == 0) {
		struct passwd* pw = getpwuid(s.st_uid);
		struct group*  gr = getgrgid(s.st_gid);

		hdr->type = S_ISDIR(s.st_mode) ? DAR_CHUNK_DIRECTORY : DAR_CHUNK_FILE;

		memset(hdr->name, 0, sizeof(hdr->name));
		memset(hdr->user, 0, sizeof(hdr->user));
		memset(hdr->group, 0, sizeof(hdr->group));

		memcpy(hdr->name, path, strlen(path));
		if(pw != NULL) memcpy(hdr->user, pw->pw_name, strlen(pw->pw_name));
		if(gr != NULL) memcpy(hdr->group, gr->gr_name, strlen(gr->gr_name));

		hdr->mode = s.st_mode & 07777;
		hdr->uid  = s.st_uid;
		hdr->gid  = s.st_gid;

		hdr->size = dar_u32be(hdr->size);
		hdr->mode = dar_u16be(hdr->mode);
		hdr->uid  = dar_u16be(hdr->uid);
		hdr->gid  = dar_u16be(hdr->gid);
		return 0;
	}
	return -1;
}
#elif defined(HAS_WINDOWS_H)
int dar_get_info(const char* path, dar_header_t* hdr) {}
#else
#error "what platform are you targetting??? please implement dar_get_info"
#endif
