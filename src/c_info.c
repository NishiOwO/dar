#include "common.h"

int dar_cmd_info(void) {
	dar_header_t hdr;
	if(!dar_info) return -1;

	dar_io = fopen(dar_input, "rb");
	if(dar_io == NULL) {
		fprintf(stderr, "could not open: %s\n", dar_input);
		return 1;
	}

	dar_printf(stdout, "PERMISSION  UID   GID  COMPRESSED SIZE         NAME");
	dar_printf(stdout, "---------- ----------- --------------- --------------------");
	while(1) {
		char name[129];
		name[128] = 0;

		dar_read(&hdr);
		if(hdr.type == DAR_CHUNK_END) break;

		memcpy(name, hdr.name, sizeof(hdr.name));
		dar_printf(stdout, "$a10 $n$a16/$n$a22 $n$a38 $v", hdr.uid, hdr.gid, hdr.size, name);

		fseek(dar_io, hdr.size, SEEK_CUR);
	}
	dar_printf(stdout, "---------- ----------- --------------- --------------------");

	fclose(dar_io);

	return 0;
}
