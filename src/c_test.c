#include "common.h"

int dar_cmd_test(void) {
	if(!dar_test) return -1;

	dar_io = fopen(dar_input, "rb");
	if(dar_io == NULL) {
		fprintf(stderr, "could not open: %s\n", dar_input);
		return 1;
	}

	fclose(dar_io);

	return 0;
}
