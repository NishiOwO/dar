#include "common.h"

int dar_cmd_create(void) {
	int	     i;
	dar_header_t hdr;
	if(!dar_create) return -1;

	dar_io = fopen(dar_input, "wb");
	if(dar_io == NULL) {
		fprintf(stderr, "could not open: %s\n", dar_input);
		return 1;
	}

	for(i = 0; i < arrlen(dar_files); i++) {
		dar_write(dar_files[i]);
	}
	memset(&hdr, 0, sizeof(hdr));
	hdr.type = DAR_CHUNK_END;
	fwrite(&hdr, 1, sizeof(hdr), dar_io);

	fclose(dar_io);

	return 0;
}
