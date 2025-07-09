#include "common.h"

void dar_write(const char* path) {
	dar_header_t hdr;
	jmp_buf	     err;

	printf("%s... ", path);
	fflush(stdout);

	if(setjmp(err)) {
		printf("failed\n");
		exit(1);
	}

	memset(&hdr, 0, sizeof(hdr));
	if(dar_get_info(path, &hdr) == 0) {
		if(hdr.type == DAR_CHUNK_DIRECTORY) {
			void* dir = dar_opendir(path);
			if(dir != NULL) {
				char* p;
				fwrite(&hdr, 1, sizeof(hdr), dar_io);
				printf("\n");
				while((p = dar_readdir(dir)) != NULL) {
					dar_write(p);
					free(p);
				}
				dar_closedir(dir);
			}
		} else {
			u8	 in[DAR_CHUNKSIZE];
			u8	 out[DAR_CHUNKSIZE];
			z_stream strm;
			u32	 total	 = 0;
			u32	 totalin = 0;
			int	 flush;
			u32	 have;
			u8*	 buf;
			int	 i;
			char	 progress[9];
			int	 prog	  = 0;
			u8**	 buffers  = NULL;
			u32*	 bufsizes = NULL;
			FILE*	 src;

#ifndef DUMB_TERMINAL
			printf(" ");
			fflush(stdout);
#endif

			strcpy(progress, "-\\|/-\\|/");

			buffers	 = NULL;
			bufsizes = NULL;

			src = fopen(path, "rb");
			if(src == NULL || deflateInit(&strm, dar_quality) != Z_OK) {
				longjmp(err, 0);
			}
			do {
				strm.avail_in = fread(in, 1, DAR_CHUNKSIZE, src);
				totalin += strm.avail_in;
				flush	     = feof(src) ? Z_FINISH : Z_NO_FLUSH;
				strm.next_in = in;
				do {
					strm.avail_out = DAR_CHUNKSIZE;
					strm.next_out  = out;
					deflate(&strm, flush);
					have = DAR_CHUNKSIZE - strm.avail_out;
					total += have;
					buf = malloc(have);

#ifdef DUMB_TERMINAL
					printf("o");
					fflush(stdout);
#else
					printf("%c%c", 8, progress[(prog++) % 8]);
					fflush(stdout);
#endif

					memcpy(buf, out, have);
					arrput(buffers, buf);
					arrput(bufsizes, have);
				} while(strm.avail_out == 0);
			} while(flush != Z_FINISH);
			deflateEnd(&strm);
			hdr.size = dar_u32be(total);

#ifdef DUMB_TERMINAL
			printf(" ");
			fflush(stdout);
#else
			printf("%c%c ", 8, 8);
			fflush(stdout);
#endif

			fwrite(&hdr, 1, sizeof(hdr), dar_io);
			for(i = 0; i < arrlen(buffers); i++) {
				fwrite(buffers[i], 1, bufsizes[i], dar_io);
				free(buffers[i]);
			}
			printf("%d -> %d\n", totalin, total);

			arrfree(buffers);
			arrfree(bufsizes);
		}
	} else {
		longjmp(err, 0);
	}
}

void dar_read(dar_header_t* hdr) {
	fread(hdr, 1, sizeof(*hdr), dar_io);
	hdr->mode = dar_u16be(hdr->mode);
	hdr->size = dar_u32be(hdr->size);
	hdr->uid  = dar_u16be(hdr->uid);
	hdr->gid  = dar_u16be(hdr->gid);
}
