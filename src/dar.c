#include <stdio.h>

#include "common.h"

#define CMD(name) if((st = dar_cmd_ ## name()) != -1) return st;

FILE* dar_io = NULL;

int main(int argc, char** argv){
	int i;
	int st = 0;
	for(i = 1; i < argc; i++){
		int st = dar_cmd(argc - 1, argv[i]);
		if(st != -1) return st;
	}
	if(dar_show_help){
		FILE* out = stderr;
		dar_printf(out, "DAr manager version $v$sCopyright(c) Nishi, 2025.$r", dar_version);
#ifdef DUMB_TERMINAL
		dar_printf(out, "  Dumb terminal output support integrated");
#endif
#ifdef HAS_DIRENT
		dar_printf(out, "  Uses dirent.h");
#endif

		dar_printf(out, "");
		dar_printf(out, "Usage: $v [-]<commands>[<options>] [-<options> ...] archive_file [file...]", argv[0]);
		dar_printf(out, "  commands:$a12[cxt]");
		dar_printf(out, "  options:$a12[v[w=<dir>][o=[0123456789]]]");
		dar_printf(out, "commands:$a40options:");
		dar_printf(out, " c   Create archive$a40 v   Verbose");
		dar_printf(out, " x   Extract from archive$a40 w   Specify extract directory");
		dar_printf(out, " t   Test archive$a40 o   Compress quality");
	}

	CMD(create);
	CMD(extract);
	CMD(test);
	CMD(info);

	return -1;
}
