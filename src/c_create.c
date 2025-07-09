#include "common.h"

int dar_cmd_create(void) {
	int i;
	if(!dar_create) return -1;

	dar_io = fopen(dar_input, "wb");
	if(dar_io == NULL) {
		fprintf(stderr, "could not open: %s\n", dar_input);
		return 1;
	}

	for(i = 0; i < arrlen(dar_files); i++) {
		dar_write(dar_files[i]);
	}

	fclose(dar_io);

	return 0;
}
