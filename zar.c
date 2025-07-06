#include <stdio.h>

#include "common.h"

int main(int argc, char** argv){
	int i;
	for(i = 1; i < argc; i++){
		int st = zar_cmd(argv[i]);
		if(st != -1) return st;
	}
	if(zar_show_help){
		FILE* out = stderr;
		zar_printf(out, "ZAr manager version $v$sCopyright(c) Nishi, 2025.$r", zar_version);
		zar_printf(out, "Usage: $v [-]<commands>[<options>] [-<options> ...] archive_file", argv[0]);
		zar_printf(out, "  commands:$a12[cxt]");
		zar_printf(out, "  options:$a12[v[w=<dir>][o=[0123456789]]]");
		zar_printf(out, "commands:$a40options:");
		zar_printf(out, " c   Create archive$a40 v   Verbose");
		zar_printf(out, " x   Extract from archive$a40 w   Specify extract directory");
		zar_printf(out, " t   Test archive$a40 o   Compress quality");
	}
}
