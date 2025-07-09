#include "common.h"

int dar_cmd_extract(void) {
	dar_header_t hdr;
	if(!dar_extract) return -1;

	dar_io = fopen(dar_input, "rb");
	if(dar_io == NULL) {
		fprintf(stderr, "could not open: %s\n", dar_input);
		return 1;
	}

	while(1) {
		char name[129];
		name[128] = 0;

		dar_read(&hdr);
		if(hdr.type == DAR_CHUNK_END) break;

		memcpy(name, hdr.name, sizeof(hdr.name));
		if(hdr.type == DAR_CHUNK_FILE){
			z_stream strm;
			u32 size = hdr.size;
			u8 in[DAR_CHUNKSIZE];
			u8 out[DAR_CHUNKSIZE];
			u32 rdsz;
			int ret;
			u32 have;

			printf("%s... ", name);
			fflush(stdout);

			strm.zalloc = Z_NULL;
			strm.zfree = Z_NULL;
			strm.opaque = Z_NULL;
			strm.avail_in = 0;
			strm.next_in = Z_NULL;
			if(inflateInit(&strm) != Z_OK){
				printf("failed\n");
				exit(1);
			}
			do{
				rdsz = size < DAR_CHUNKSIZE ? size : DAR_CHUNKSIZE;
				strm.avail_in = fread(in, 1, rdsz, dar_io);
				strm.next_in = in;
				do {
					strm.avail_out = DAR_CHUNKSIZE;
					strm.next_out = out;
					ret = inflate(&strm, Z_NO_FLUSH);
					if(ret == Z_NEED_DICT || ret == Z_DATA_ERROR || ret == Z_MEM_ERROR){
						inflateEnd(&strm);
						printf("failed\n");
						exit(1);
					}
					have = DAR_CHUNKSIZE - strm.avail_out;
				}while(strm.avail_out == 0);
			}while(ret != Z_STREAM_END);
			inflateEnd(&strm);
			printf("\n");
		}else{
			if(hdr.type == DAR_CHUNK_DIRECTORY){
				printf("%s... ", name);
				fflush(stdout);
				dar_mkdir(name, hdr.mode);
				printf("\n");
			}
			fseek(dar_io, hdr.size, SEEK_CUR);
		}
	}

	fclose(dar_io);

	return 0;
}
